#include "python.hpp"

namespace bp = boost::python;
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
	class_<entity>("entity")
		.def("getCoords",&entity::getCoords);


	

	class_<PhysicalEntity,bases<entity> >("PhysicalEntity");
	
	

	class_<objectEntity,bases<PhysicalEntity> >("objectEntity");

	class_<obj_list>("obj_list")
		 .def(vector_indexing_suite<obj_list>() );

	
	class_<lights_list>("lights_list")
        .def(vector_indexing_suite<lights_list>() );

  
	
	class_<world,shared_ptr<world>,boost::noncopyable>("world",no_init)//.add_property("instance", shared_ptr<&world::getInstance>())
        .def("getInstance",&getSharedInstance )
		.staticmethod("getInstance")
		.def("getLights", &world::getLights)
		.def("getModels", &world::getModels)

		//.def("getInstance",&world::getInstance)
		
		
		
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
 
 cout << "Loaded python script " << filename << endl;
}

void PyManipulator::signal(string name,void *params) {
	string sigcode;
	
		sigcode=iname+".on"+name+"()";

	
//cout << "Signal " << sigcode << endl;
	PyRun_SimpleString(sigcode.c_str());
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

	broadcast("SelfLoad",0);
}

PyScripting::PyScripting() {
	Py_Initialize();
	 initworld();
}

PyScripting::~PyScripting() {
	Py_Finalize();
}


void PyScripting::broadcast(string name,void *params) {
	for(int i=0; i<manipulators.size(); i++) {
		manipulators[i]->signal(name,params);
	}
}