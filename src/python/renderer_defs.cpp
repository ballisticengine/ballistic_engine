#include "python/renderer_defs.hpp"
#include "renderer/RendererInterface.hpp"
#include "renderer/RenderingManager.hpp"

boost::shared_ptr<RenderingManager> getSharedRenderingManagerInstance() {
    return boost::shared_ptr<RenderingManager>(RenderingManager::getInstance(), NullDeleter());
}

BOOST_PYTHON_MODULE(Rendering) {
    bp::class_<RenderingManager,
            boost::shared_ptr<RenderingManager>,
            boost::noncopyable>("RenderingManager", bp::no_init)
            .def("get_renderer", &RenderingManager::getRenderer, bp::return_value_policy<bp::reference_existing_object>())
            .def("get_instance", &getSharedRenderingManagerInstance)
            .staticmethod("get_instance")
            ;
    
    bp::class_<RendererInterface, RendererInterface *>("rendering_interface", bp::no_init)
            .def("unproject", &RendererInterface::unproject)
            ;
}

void init_renderer() {
    initRendering();
}