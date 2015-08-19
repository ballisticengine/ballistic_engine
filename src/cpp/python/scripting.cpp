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
    init_timer();
    init_renderer();
    init_engine();

}

PyScripting::~PyScripting() {
    Py_Finalize();
}

void PyScripting::broadcast(string name, initializer_list<void *> params,
        bool check_existing) {


    this->lockWait();

    for (int i = 0; i < manipulators.size(); i++) {
        if (check_existing && !manipulators[i]->hasSignal(name)) {
            continue;
        }
        manipulators[i]->signal(name, params);
    }
    m.unlock();
}

//void PyScripting::broadcast(string name,
//        map<string, string> params, bool check_existing) {
//
//    bp::dict d = toPythonDict(params);
//    this->broadcast(name, {(void *)&d}, true);
//}

void PyScripting::enqueue(string name,
        initializer_list<void *> params, bool check_existing) {
    
    SignalType signal;
    signal.name = name;
    signal.params = params;
    signal.check_existing = check_existing;
    sig_queue.push(signal);
    
}

void PyScripting::clear_queue() {
    while(!sig_queue.empty()) {
        sig_queue.pop();
    }
}

void PyScripting::runQueue() {
    while(!sig_queue.empty()) {
        SignalType signal = sig_queue.front();
        sig_queue.pop();
        this->broadcast(signal.name, signal.params, signal.check_existing);
    }
}

void PyScripting::lockWait() {
    while (!m.try_lock()) {
    };
}

man_vector PyScripting::getManipulatorsV() {
    return manipulators;
}

PyManipulator* PyScripting::getManipulator(string name) {
    return manipulators_map[name];
}