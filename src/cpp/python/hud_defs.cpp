#include "python/hud_defs.hpp"
#include "python/null_deleter.hpp"

shared_ptr<HUD> getSharedHUDInstance() {
    return shared_ptr<HUD>(HUD::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<HUD> hud_ptr;

typedef boost::shared_ptr<void *> void_ptr;

BOOST_PYTHON_MODULE(HUD) {

    bp::class_<Texture, Texture*>("texture")
            .def("get_pixels", &Texture::getPixels, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("set_pixels", &Texture::setPixels)
            .def("get_surface", &Texture::getSurface, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("set_surface", &Texture::setSurface)
            .def("get_width", &Texture::getWidth)
            .def("get_height", &Texture::getHeight)
            ;

    bp::class_<UiImage, UiImage *>("UiImage")
            .def_readwrite("tex", &UiImage::tex)
            .def("set_text",&UiImage::setText)
                    ;
    bp::class_<HUD, shared_ptr<HUD>, boost::noncopyable>("HUD", bp::no_init)
            .def("get_instance", &getSharedHUDInstance)
            .def("get_image", &HUD::getImage, bp::return_value_policy< bp::return_opaque_pointer >())
            

            //.def("getImages",&HUD::getImages)
            ;
};

void init_hud() {
    initHUD();
}