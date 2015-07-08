#include "python/engine_defs.hpp"
#include "python/null_deleter.hpp"

shared_ptr<EngineState> getSharedEngineStateInstance() {
    return shared_ptr<EngineState>(EngineState::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<EngineState> engine_state_ptr;

BOOST_PYTHON_MODULE(EngineState) {
    bp::class_<EngineState, EngineState*>("EngineState")
            .def("setBool", &EngineState::setBool)
            .def("getBool", &EngineState::getBool)
            .def("setString", &EngineState::setString)
            .def("toggleBool", &EngineState::toggleBool)
            ;
}

void init_engine() {
    initEngineState();
}