#include "python/engine_defs.hpp"
#include "python/null_deleter.hpp"

boost::shared_ptr<EngineState> getSharedEngineStateInstance() {
    return boost::shared_ptr<EngineState>(EngineState::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<EngineState> engine_state_ptr;

BOOST_PYTHON_MODULE(Engine) {
    bp::class_<EngineState, boost::shared_ptr<EngineState>, boost::noncopyable>
    ("EngineState",  bp::no_init)
            .def("get_instance", &getSharedEngineStateInstance)
            .staticmethod("get_instance")
            .def("set_bool", &EngineState::setBool)
            .def("get_bool", &EngineState::getBool)
            .def("set_string", &EngineState::setString)
            .def("get_string", &EngineState::getString)
            ;
}

void init_engine() {
    initEngine();
}