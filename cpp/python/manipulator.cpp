#include "python/manipulator.hpp"
#include "entities/entity.hpp"
#include "entities/physicalEntity.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/mathTypes.hpp"
#include "world/World.hpp"

PyManipulator::PyManipulator(string file) {

    code = Utils::loadText(file);
    filename = boost::filesystem::basename(file);
    PyRun_SimpleString(code);
    boost::filesystem::path p(filename);
    classname = p.stem().string();
    iname = classname + "_instance";
    string codeinit = iname + "=" + classname + "()";
    cout << "INIT: " << codeinit << endl;
    PyRun_SimpleString(codeinit.c_str());
    module = bp::import("__main__");
    instance = module.attr(iname.c_str());
    cout << "Loaded python script " << filename << endl;
}

template <typename T> bp::list PyManipulator::arrayToList(T *array) {
    bp::list a;
    for (size_t i = 0; i < 255; i++) {
        a.append(array[i]);
    }
    return a;
}

void PyManipulator::signal(string name, void *paramA, void *paramB, void* paramC, void* paramD) {
    Py_BEGIN_ALLOW_THREADS
    PyLocker::getInstance()->lock();
    string signame = "on" + name;
    bp::object f = bp::extract<bp::object>(instance.attr(signame.c_str()));
    World *w = World::getInstance();
    HUD *h = HUD::getInstance();
    try {
        if (name == "Init") {
            //static Timer *t=new Timer();
            f(boost::ref(*w), boost::ref(*h));
        } else if (name == "EntityCollision") {
            PhysicalEntity *a, *b;
            a = (PhysicalEntity *) paramA;
            b = (PhysicalEntity *) paramB;
            //vector cvec=*(vector *)paramC;
            CollsionInfo ci = *(CollsionInfo *) paramC;
            f(boost::ref(*a), boost::ref(*b), boost::ref(ci));
        } else if (name == "EntityMovement") {
            PhysicalEntity *a;
            a = (PhysicalEntity *) paramA;
            f(boost::ref(*a));
        } else if (name == "LevelCollision") {
            PhysicalEntity *a;
            a = (PhysicalEntity *) paramA;
            RoomEntity *r = (RoomEntity *) paramB;
            Vector3d cvec = *(Vector3d *) paramC;
            f(boost::ref(*a), boost::ref(*r), boost::ref(cvec));
        } else if (name == "MouseMove") {

            int *a = (int *) paramA;
            int *b = (int *) paramB;
            f(*a, *b);

        } else if (name == "KeyDown" || name == "KeyUp" ) {
            Uint8 **keyboard_state = (Uint8**) paramA;
            bp::list a=PyManipulator::arrayToList(*keyboard_state);
            f(a);
        } else {
            f();
        }
    } catch (const bp::error_already_set& e) {
        cout << "PyError:\n";
        assert(PyErr_Occurred());
        PyErr_Print();
    }

    PyLocker::getInstance()->unlock();
    Py_END_ALLOW_THREADS

}

PyManipulator::~PyManipulator() {
    delete code;
}

