#include "python/manipulator.hpp"
#include "entities/entity.hpp"
#include "entities/physicalEntity.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/mathTypes.hpp"
#include "world/World.hpp"

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
	World *w=World::getInstance();
        HUD *h=HUD::getInstance();
	try {
	if(name=="Init") {
            //static Timer *t=new Timer();
                f(boost::ref(*w),boost::ref(*h));
	} else if(name=="EntityCollision") {
		PhysicalEntity *a,*b;
		a=(PhysicalEntity *)paramA;
		b=(PhysicalEntity *)paramB;
		//MathTypes::vector cvec=*(MathTypes::vector *)paramC;
                CollsionInfo ci=*(CollsionInfo *)paramC;
		f(boost::ref(*a),boost::ref(*b),boost::ref(ci));
	} else if(name=="EntityMovement") {
		PhysicalEntity *a;
		a=(PhysicalEntity *)paramA;	
		f(boost::ref(*a));
	} else if(name=="LevelCollision") {
		PhysicalEntity *a;
		a=(PhysicalEntity *)paramA;	
		RoomEntity *r=(RoomEntity *)paramB;
                MathTypes::Vector3d cvec=*(MathTypes::Vector3d *)paramC;
		f(boost::ref(*a),boost::ref(*r),boost::ref(cvec));
	} else if(name=="ObserverStateChange") {
            ObserverState *s=(ObserverState *)paramA;
            f(boost::ref(s));
        } 
        
        else {
		f();
	}
        }catch(const bp::error_already_set& e) {
            cout << "PyError:\n";
             assert(PyErr_Occurred());
             PyErr_Print();
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

