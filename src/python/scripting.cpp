#include "python/scripting.hpp"

void PyScripting::init() {
    Py_Initialize();
    PyEval_InitThreads();

    init_types();
    init_ui();
    init_world();
    init_timer();
    init_renderer();
    init_engine();

}

void PyScripting::loadManipulator(string path, string name) {
    string fn = path + "/" + name + ".py";
    PyManipulator *pyman = new PyManipulator(fn);
    manipulators.push_back(pyman);
    manipulators_map[name] = pyman;
}

void PyScripting::loadManipulators() {

    vector<string> scripts = Config::getInstance()->getScripts();
    for (int i = 0; i < scripts.size(); i++) {
        string path = string(CONFIG_DIR) + DS + string(COMMON_DIR) + DS + string("python");

        loadManipulator(path, scripts[i]);
    }

    broadcast("self_load",{0});
}

PyScripting::PyScripting() {


}

void PyScripting::cleanup() {
    //TODO: cleanup manipulators and scripts
    Py_Finalize();
}

PyScripting::~PyScripting() {

}

void PyScripting::addScript(string name, string path) {
    scripts[name] = new Script(path);
}

void PyScripting::runScript(string name) {
    scripts[name]->run();
}

void PyScripting::broadcast(string name, initializer_list<void *> params,
        bool check_existing, bool ui_signal) {

    this->lockWait();

    for (int i = 0; i < manipulators.size(); i++) {
        if (check_existing && !manipulators[i]->hasSignal(name)) {
            continue;
        }
        manipulators[i]->signal(name, params, ui_signal);
    }
    m.unlock();
}

void PyScripting::enqueue(string name,
        initializer_list<void *> params, bool check_existing) {

    //cout << "Enqueue " << sig_queue.size() << endl;

    SignalType signal;
    signal.name = name;
    signal.params = params;
    signal.check_existing = check_existing;
    sig_queue.push(signal);

}

void PyScripting::clear_queue() {
    while (!sig_queue.empty()) {
        sig_queue.pop();
    }
}

void PyScripting::runQueue() {
    while (!sig_queue.empty()) {
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