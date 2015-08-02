#include "python/renderer_defs.hpp"
#include "renderer/RendererInterface.hpp"
#include "renderer/RenderingManager.hpp"

BOOST_PYTHON_MODULE(RenderingManager) {
    bp::class_<RenderingManager,
            shared_ptr<RenderingManager>,
            boost::noncopyable>("rendering_manager", bp::no_init)
            .def("get_renderer", &RenderingManager::getRenderer, bp::return_value_policy<bp::reference_existing_object>())
            ;
}

BOOST_PYTHON_MODULE(RendererInterface) {
    // unproject .def("reset", &Coords::reset)
    
    bp::class_<RendererInterface, RendererInterface *>("rendering_interface", bp::no_init)
            .def("unproject", &RendererInterface::unproject)
            ;
}

void init_renderer() {
    initRenderingManager();
    initRendererInterface();
}