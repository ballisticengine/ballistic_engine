#include "python/scripting.hpp"

void PyScripting::loadManipulators() {

    vector<string> scripts = Config::getInstance()->getScripts();
    for (int i = 0; i < scripts.size(); i++) {
        string pyfn = string(CONFIG_DIR) + DS + string(COMMON_DIR) + DS +
                string("python") + DS + scripts[i] + ".py";
        cout << "Global python script: " << pyfn << endl;
        PyManipulator *pyman = new PyManipulator(pyfn);
        manipulators.push_back(pyman);
        manipulators_map[scripts[i]] = pyman;
    }

    broadcast("self_load",{0});
}

PyScripting::PyScripting() {
    Py_Initialize();
    PyEval_InitThreads();
    init_types();
    init_world();
    init_hud();
    init_timer();
    init_renderer();
    init_engine();

}

PyScripting::~PyScripting() {
    Py_Finalize();
}

void PyScripting::broadcast(string name, initializer_list<void *> params) {


    this->lockWait();

    for (int i = 0; i < manipulators.size(); i++) {
        manipulators[i]->signal(name, params);
    }
    m.unlock();
}

void PyScripting::lockWait() {
    while (!m.try_lock()) {
    };
}

void PyScripting::broadcastExisting(string name, initializer_list<void *> params) {
    this->lockWait();

    for (int i = 0; i < manipulators.size(); i++) {
        if (manipulators[i]->hasSignal(name)) {
            manipulators[i]->signal(name, params);
        }
    }
    m.unlock();
}

man_vector PyScripting::getManipulatorsV() {
    return manipulators;
}

PyManipulator* PyScripting::getManipulator(string name) {
    return manipulators_map[name];
}