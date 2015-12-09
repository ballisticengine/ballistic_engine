#include "python/manipulator.hpp"
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/Vector3d.hpp"
#include "world/World.hpp"
#include "config/EngineState.hpp"
#include "renderer/RenderingManager.hpp"
#include "ui/UISignalData.hpp"
#include "world/WorldManager.hpp"

PyManipulator::PyManipulator(string filename) :  ScriptBase(filename) {
    this->filename = boost::filesystem::basename(filename);
    boost::filesystem::path p(filename);
    classname = p.stem().string();
    iname = classname + "_instance";
    string codeinit = iname + "=" + classname + "()";
    cout << "INIT: " << codeinit << endl;

    try {
        PyRun_SimpleString(code);
        PyRun_SimpleString(codeinit.c_str());
        module = bp::import("__main__");
        instance = module.attr(iname.c_str());
    } catch (bp::error_already_set) {
        PyErr_Print();
    }

    cout << "Loaded python script " << filename << endl;

}

template <typename T> bp::list PyManipulator::arrayToList(T *array) {
    bp::list a;
    for (size_t i = 0; i < 255; i++) {
        a.append(array[i]);
    }
    return a;
}



void PyManipulator::signal(string name, initializer_list<void *> params, bool ui_signal) {
    //TODO: move those to lock and unlockthreads
    Py_BEGIN_ALLOW_THREADS
    PyLocker::getInstance()->lock();
    vector<void *> params_v(params);
    bp::object f = bp::extract<bp::object>(instance.attr(name.c_str()));
    World *w = WorldManager::getInstance()->getCurrentWorld();
    
    RenderingManager *rm = RenderingManager::getInstance();
    EngineState *es = EngineState::getInstance();
    try {
        if (name == "entity_collision") {
            ObjectEntity *a, *b;
            a = (ObjectEntity *) params_v[0];
            b = (ObjectEntity *) params_v[1];
            CollisionInfo ci = *(CollisionInfo *) params_v[2];
            f(boost::ref(*a), boost::ref(*b), boost::ref(ci));
        } else if (name == "entity_movement") {
            ObjectEntity *a;
            a = (ObjectEntity *) params_v[0];
            f(boost::ref(*a));
        } else if (name == "level_collision") {
            ObjectEntity *a;
            a = (ObjectEntity *) params_v[0];
            RoomEntity *r = (RoomEntity *) params_v[1];
            CollisionInfo cvec = *(CollisionInfo *) params_v[2];
            f(boost::ref(*a), boost::ref(*r), boost::ref(cvec));
        } else if (name == "mouse_move") {

            int *a = (int *) params_v[0];
            int *b = (int *) params_v[1];
            f(*a, *b);

        } else if (name == "mouse_click") {

            unsigned int *a = (unsigned int *) params_v[0];
            f(*a);

        } else if (name == "key_down") {
            Uint8 **keyboard_state = (Uint8**) params_v[0];
            bp::list a = PyManipulator::arrayToList(*keyboard_state);
            f(a);
        } else if (name == "key_up") {
            Uint8 *keyboard_state = (Uint8*) params_v[0];
            bp::list a = PyManipulator::arrayToList(keyboard_state);
            f(a);
        } else if (name == "key_press") {
            int *key = (int *) params_v[0];
            f(*key);

        } else {
            if(ui_signal && params_v[0]!=0) {
                UISignalData *data = (UISignalData *)params_v[0];
                f(*data);
                delete data;
            } else {
                f();
            }
        }
    } catch (const bp::error_already_set& e) {
        cout << "PyError:\n";
        assert(PyErr_Occurred());
        PyErr_Print();
    }

    PyLocker::getInstance()->unlock();
    Py_END_ALLOW_THREADS

}

bool PyManipulator::hasSignal(string name) {
    bool result = true;
    Py_BEGIN_ALLOW_THREADS
    PyLocker::getInstance()->lock();
    try {
        bp::object sig = bp::extract<bp::object>(instance.attr(name.c_str()));
    } catch (const bp::error_already_set& e) {

        result = false;
    }
    PyLocker::getInstance()->unlock();
    Py_END_ALLOW_THREADS
    return result;
}


void PyManipulator::lockThreads() {
    //    Py_BEGIN_ALLOW_THREADS
    //    PyLocker::getInstance()->lock();
}

void PyManipulator::unlockThreads() {
    //    PyLocker::getInstance()->unlock();
    //    Py_END_ALLOW_THREADS
}
