#include "python/ui_defs.hpp"
#include "python/null_deleter.hpp"
#include "ui/rocket_context.hpp"

boost::shared_ptr<UI> getSharedUIInstance() {
    return boost::shared_ptr<UI>(UI::getInstance(), NullDeleter());
}





//typedef ElementDocument* (*el_str)(const String& document_path);


BOOST_PYTHON_MODULE(BallisticUI) {    
    
    bp::class_<UI,  boost::shared_ptr<UI>, boost::noncopyable>("UI", bp::no_init)
    .def("get_instance", &getSharedUIInstance)
    .staticmethod("get_instance")
    
    
    .def("get_context", &UI::getContext, bp::return_value_policy<bp::reference_existing_object>())
    
    .def("add_document", &UI::addDocument)
    .def("set_content_by_id", &UI::setContentByID)
    .def("show_doc", &UI::showDoc);
    ;
    
    bp::class_<RC::ElementDocument, RC::ElementDocument *>("element_document", bp::no_init)
    
   // .def("__init__", bp::make_constructor(&RC::ElementDocument::ElementDocument))
    ;
    

    
}

void init_ui() {
    initBallisticUI();
}
