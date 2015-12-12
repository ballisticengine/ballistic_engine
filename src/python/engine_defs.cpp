#include "python/engine_defs.hpp"
#include "python/null_deleter.hpp"

boost::shared_ptr<EngineState> getSharedEngineStateInstance() {
    return boost::shared_ptr<EngineState>(EngineState::getInstance(), NullDeleter());
}

boost::shared_ptr<ResourceManager> getSharedResourceManagerInstance() {
    return boost::shared_ptr<ResourceManager>(ResourceManager::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<EngineState> engine_state_ptr;
typedef boost::shared_ptr<ResourceManager> resman_state_ptr;

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

    bp::class_<ResourceManager, boost::shared_ptr<ResourceManager>, boost::noncopyable>("ResourceManager", bp::no_init)
        .def("get_instance", &getSharedResourceManagerInstance)
        .staticmethod("get_instance")
    ;

}

void init_engine() {
    initEngine();
}