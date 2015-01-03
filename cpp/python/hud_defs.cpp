#include "python/hud_defs.hpp"
#include "python/null_deleter.hpp"

shared_ptr<HUD> getSharedHUDInstance() {
    return shared_ptr<HUD>(HUD::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<HUD> hud_ptr;

typedef boost::shared_ptr<void *> void_ptr;

BOOST_PYTHON_MODULE(HUD) {

    bp::class_<texture, texture*>("texture")
            .def("getPixels", &texture::getPixels, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("setPixels", &texture::setPixels)
            .def("getSurface", &texture::getSurface, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("setSurface", &texture::setSurface)
            .def("getWidth", &texture::getWidth)
            .def("getHeight", &texture::getHeight)
            ;

    bp::class_<UiImage, UiImage *>("UiImage")
            .def_readwrite("tex", &UiImage::tex);

    bp::class_<HUD, shared_ptr<HUD>, boost::noncopyable>("HUD", bp::no_init)
            .def("getInstance", &getSharedHUDInstance)
            .def("getImage", &HUD::getImage, bp::return_value_policy< bp::return_opaque_pointer >())

            //.def("getImages",&HUD::getImages)
            ;
};

void init_hud() {
    initHUD();
}