#include "python/python.hpp"


struct NullDeleter
{
	void operator()(const void*){}
};

shared_ptr<world> getSharedInstance()
{
	return shared_ptr<world>( world::getInstance(),NullDeleter() );
}

typedef boost::shared_ptr<world> world_ptr;
BOOST_PYTHON_MODULE(world)
{

	bp::class_<MathTypes::vector,MathTypes::vector *>("Vector3d")
		.def_readwrite("x",&MathTypes::vector::x)
		.def_readwrite("y",&MathTypes::vector::y)
		.def_readwrite("z",&MathTypes::vector::z)
		.def("write",&MathTypes::vector::write)
		;

	bp::class_<TrRot,TrRot *>("TrRot")
		.def_readwrite("t",&TrRot::t)
		.def_readwrite("r",&TrRot::r)
		.def("reset",&TrRot::reset)
		;

	bp::class_<ShapeAbstract,ShapeAbstract *>("ShapeAbstract");
	bp::class_<shape,shape *,bp::bases<ShapeAbstract> >("shape");




	bp::class_<entity,entity *>("entity")
		.def("getCoords",&entity::getCoords)
		.def("locate",&entity::locate)
		.def_readonly("name",&entity::name)
		.def_readonly("type",&entity::type)
		;



	bp::class_<PhysicalEntity,PhysicalEntity*,bp::bases<entity> >("PhysicalEntity")
		.def("getVelocity",&PhysicalEntity::getVelocity)
		.def("setVelocity",&PhysicalEntity::setVelocity)
		.def_readwrite("velocity",&PhysicalEntity::velocity)

		;


	bp::class_<ObjectEntity,ObjectEntity*,bp::bases<PhysicalEntity> >("ObjectEntity")
		.def_readwrite("model",&ObjectEntity::model)
		;

	bp::class_<obj_list>("obj_list")
		.def(bp::vector_indexing_suite<obj_list>() );


	bp::class_<roomEntity,roomEntity *,bp::bases<ObjectEntity> >("roomEntity")
		.def_readwrite("models",&roomEntity::models)
		;

	bp::class_<lights_list>("lights_list")
		.def(bp::vector_indexing_suite<lights_list>() );



	bp::class_<world,shared_ptr<world>,boost::noncopyable>("world",bp::no_init)//.add_property("instance", shared_ptr<&world::getInstance>())
		.def("getInstance",&getSharedInstance )
		.def_readonly("active_room", &world::active_room)
		
		.staticmethod("getInstance")
				
		;


};



PyManipulator::PyManipulator(string file) {

	code=Utils::loadText(file);
	filename=boost::filesystem::basename(file);
	PyRun_SimpleString(code);
	boost::filesystem::path p(filename);
	classname=p.stem().string();
	iname=classname+"_instance";
	string codeinit=iname+"="+classname+"()";

	cout << "INIT: " << codeinit << endl;
	PyRun_SimpleString(codeinit.c_str());
	module = bp::import("__main__");
	instance=module.attr(iname.c_str());
	cout << "Loaded python script " << filename << endl;
}



void PyManipulator::signal(string name,void *paramA,void *paramB,void* paramC,void* paramD) {
	Py_BEGIN_ALLOW_THREADS
		PyLocker::getInstance()->lock();
	string signame="on"+name;
	bp::object f=bp::extract<bp::object>(instance.attr(signame.c_str()));
	world *w=world::getInstance();
	
	if(name=="Init") {
		f(boost::ref(*w));
	} else if(name=="EntityCollision") {
		PhysicalEntity *a,*b;
		a=(PhysicalEntity *)paramA;
		b=(PhysicalEntity *)paramB;
		MathTypes::vector cvec=*(MathTypes::vector *)paramC;
		f(boost::ref(*a),boost::ref(*b),boost::ref(cvec));
	} else if(name=="EntityMovement") {
		PhysicalEntity *a;
		a=(PhysicalEntity *)paramA;	
		f(boost::ref(*a));
	} else if(name=="LevelCollision") {
		PhysicalEntity *a;
		a=(PhysicalEntity *)paramA;	
		roomEntity *r=(roomEntity *)paramB;
		f(boost::ref(*a),boost::ref(*r));
	} else {
		f();
	}

	//sigcode=iname+".on"+name+"()";
	PyLocker::getInstance()->unlock();
	Py_END_ALLOW_THREADS

		//cout << "Signal " << sigcode << endl;
		//PyRun_SimpleString(sigcode.c_str());
}

PyManipulator::~PyManipulator() {
	delete code;
}


//////////////////

void PyScripting::loadManipulators() {
	namespace fs = boost::filesystem;
	fs::path py_dir("python/manipulators/");
	fs::directory_iterator end_iter;
	for( fs::directory_iterator dir_iter(py_dir) ; dir_iter != end_iter ; ++dir_iter) {
		if (fs::is_regular_file(dir_iter->status()) ) {
			PyManipulator *pyman=new PyManipulator(dir_iter->path().string());
			manipulators.push_back(pyman);
		}
	}

	broadcast("Init",0);
	broadcast("SelfLoad",0);
}

PyScripting::PyScripting() {
	Py_Initialize();
	PyEval_InitThreads(); 
	initworld();
}

PyScripting::~PyScripting() {
	Py_Finalize();
}


void PyScripting::broadcast(string name,void *paramA,void *paramB,void* paramC,void* paramD) {
	for(int i=0; i<manipulators.size(); i++) {
		manipulators[i]->signal(name,paramA,paramB,paramC,paramD);
	}
}


void PyLocker::lock() {
	state = PyGILState_Ensure();
}

void PyLocker::unlock() {
	PyGILState_Release(state);
}