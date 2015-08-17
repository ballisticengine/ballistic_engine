#include "python/hud_defs.hpp"
#include "python/null_deleter.hpp"

boost::shared_ptr<HUD> getSharedHUDInstance() {
    return boost::shared_ptr<HUD>(HUD::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<HUD> hud_ptr;

typedef boost::shared_ptr<void *> void_ptr;

BOOST_PYTHON_MODULE(HUD) {

    bp::class_<Ballistic::Types::Texture, Ballistic::Types::Texture*>("texture")
            .def("get_pixels", &Ballistic::Types::Texture::getPixels, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("set_pixels", &Ballistic::Types::Texture::setPixels)
            .def("get_surface", &Ballistic::Types::Texture::getSurface, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("set_surface", &Ballistic::Types::Texture::setSurface)
            .def("get_width", &Ballistic::Types::Texture::getWidth)
            .def("get_height", &Ballistic::Types::Texture::getHeight)
            ;

    bp::class_<UiImage, UiImage *>("UiImage")
            .def_readwrite("tex", &UiImage::tex)
            .def("set_text",&UiImage::setText)
                    ;
    bp::class_<HUD, boost::shared_ptr<HUD>, boost::noncopyable>("HUD", bp::no_init)
            .def("get_instance", &getSharedHUDInstance)
            .staticmethod("get_instance")
            .def("get_image", &HUD::getImage, bp::return_value_policy< bp::return_opaque_pointer >())
            ;
};

void init_hud() {
    initHUD();
}