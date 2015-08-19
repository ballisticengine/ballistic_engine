#include "python/ui_defs.hpp"
#include "python/null_deleter.hpp"

boost::shared_ptr<UI> getSharedUIInstance() {
    return boost::shared_ptr<UI>(UI::getInstance(), NullDeleter());
}

BOOST_PYTHON_MODULE(BallisticUI) {    
    bp::class_<UI,  boost::shared_ptr<UI>, boost::noncopyable>("UI", bp::no_init)
    .def("get_instance", &getSharedUIInstance)
    .staticmethod("get_instance")
    ;
}

void init_ui() {
    initBallisticUI();
}
