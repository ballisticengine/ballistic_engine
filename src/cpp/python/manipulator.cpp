#include "python/manipulator.hpp"
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/mathTypes.hpp"
#include "world/World.hpp"
#include "config/EngineState.hpp"
#include "renderer/RenderingManager.hpp"

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

//better assign signals from python to concrete events
//like sdlio::assignSingnal or something

void PyManipulator::signal(string name, void *paramA, void *paramB, void* paramC, void* paramD) {
    
    Py_BEGIN_ALLOW_THREADS
    PyLocker::getInstance()->lock();
    
    bp::object f = bp::extract<bp::object>(instance.attr(name.c_str()));
    World *w = World::getInstance();
    HUD *h = HUD::getInstance();
    RenderingManager *rm = RenderingManager::getInstance();
    EngineState *es = EngineState::getInstance();
    try {
        if (name == "init") {
            //static Timer *t=new Timer();
            f(boost::ref(*w), boost::ref(*h), boost::ref(*es), boost::ref(*rm));
        } else if (name == "entity_collision") {
            ObjectEntity *a, *b;
            a = (ObjectEntity *) paramA;
            b = (ObjectEntity *) paramB;
            //vector cvec=*(vector *)paramC;
            CollisionInfo ci = *(CollisionInfo *) paramC;
            f(boost::ref(*a), boost::ref(*b), boost::ref(ci));
        } else if (name == "entity_movement") {
            ObjectEntity *a;
            a = (ObjectEntity *) paramA;
            f(boost::ref(*a));
        } else if (name == "level_collision") {
            ObjectEntity *a;
            a = (ObjectEntity *) paramA;
            RoomEntity *r = (RoomEntity *) paramB;
            CollisionInfo cvec = *(CollisionInfo *) paramC;
            f(boost::ref(*a), boost::ref(*r), boost::ref(cvec));
        } else if (name == "mouse_move") {

            int *a = (int *) paramA;
            int *b = (int *) paramB;
            f(*a, *b);

        } 
        else if (name == "mouse_click") {

            unsigned int *a = (unsigned int *) paramA;
            f(*a);

        } else if (name == "key_down") {
            Uint8 **keyboard_state = (Uint8**) paramA;
            bp::list a = PyManipulator::arrayToList(*keyboard_state);
            f(a);
        } else if (name == "key_up") {
            Uint8 *keyboard_state = (Uint8*) paramA;
            bp::list a = PyManipulator::arrayToList(keyboard_state);
            f(a);
        } else if (name == "key_press") {
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

