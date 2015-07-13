#include "python/manipulator.hpp"
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/mathTypes.hpp"
#include "world/World.hpp"
#include "config/EngineState.hpp"

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
    EngineState *es = EngineState::getInstance();
    try {
        if (name == "Init") {
            //static Timer *t=new Timer();
            f(boost::ref(*w), boost::ref(*h), boost::ref(*es));
        } else if (name == "EntityCollision") {
            ObjectEntity *a, *b;
            a = (ObjectEntity *) paramA;
            b = (ObjectEntity *) paramB;
            //vector cvec=*(vector *)paramC;
            CollisionInfo ci = *(CollisionInfo *) paramC;
            f(boost::ref(*a), boost::ref(*b), boost::ref(ci));
        } else if (name == "EntityMovement") {
            ObjectEntity *a;
            a = (ObjectEntity *) paramA;
            f(boost::ref(*a));
        } else if (name == "LevelCollision") {
            ObjectEntity *a;
            a = (ObjectEntity *) paramA;
            RoomEntity *r = (RoomEntity *) paramB;
            CollisionInfo cvec = *(CollisionInfo *) paramC;
            f(boost::ref(*a), boost::ref(*r), boost::ref(cvec));
        } else if (name == "MouseMove") {

            int *a = (int *) paramA;
            int *b = (int *) paramB;
            f(*a, *b);

        } else if (name == "KeyDown") {
            Uint8 **keyboard_state = (Uint8**) paramA;
            bp::list a = PyManipulator::arrayToList(*keyboard_state);
            f(a);
        } else if (name == "KeyUp") {
            Uint8 *keyboard_state = (Uint8*) paramA;
            bp::list a = PyManipulator::arrayToList(keyboard_state);
            f(a);
        } else if (name == "KeyPress") {
            int *key = (int *)paramA;
            f(*key);

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

