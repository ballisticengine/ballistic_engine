#include "python/engine_defs.hpp"
#include "python/null_deleter.hpp"

shared_ptr<EngineState> getSharedEngineStateInstance() {
    return shared_ptr<EngineState>(EngineState::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<EngineState> engine_state_ptr;

BOOST_PYTHON_MODULE(EngineState) {
    bp::class_<EngineState, EngineState*>("EngineState")
            .def("set_bool", &EngineState::setBool)
            .def("get_bool", &EngineState::getBool)
            .def("set_string", &EngineState::setString)
            .def("get_string", &EngineState::toggleBool)
            ;
}

void init_engine() {
    initEngineState();
}