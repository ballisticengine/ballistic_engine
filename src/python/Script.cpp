#include "python/Script.hpp"
#include "misc/utils.hpp"

Script::Script(string filename) : ScriptBase(filename) {
}

void Script::run() {
     try {
        PyRun_SimpleString(code);
    } catch (bp::error_already_set) {
        PyErr_Print();
    }
}