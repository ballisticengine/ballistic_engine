#include "python/hud_defs.hpp"
#include "python/null_deleter.hpp"

shared_ptr<HUD> getSharedHUDInstance() {
    return shared_ptr<HUD>(HUD::getInstance(), NullDeleter());
}

typedef boost::shared_ptr<HUD> hud_ptr;

typedef boost::shared_ptr<void *> void_ptr;

BOOST_PYTHON_MODULE(HUD) {

    bp::class_<Texture, Texture*>("texture")
            .def("getPixels", &Texture::getPixels, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("setPixels", &Texture::setPixels)
            .def("getSurface", &Texture::getSurface, bp::return_value_policy< bp::return_opaque_pointer >())
            .def("setSurface", &Texture::setSurface)
            .def("getWidth", &Texture::getWidth)
            .def("getHeight", &Texture::getHeight)
            ;

    bp::class_<UiImage, UiImage *>("UiImage")
            .def_readwrite("tex", &UiImage::tex)
            .def("setText",&UiImage::setText)
                    ;
    bp::class_<HUD, shared_ptr<HUD>, boost::noncopyable>("HUD", bp::no_init)
            .def("getInstance", &getSharedHUDInstance)
            .def("getImage", &HUD::getImage, bp::return_value_policy< bp::return_opaque_pointer >())
            

            //.def("getImages",&HUD::getImages)
            ;
};

void init_hud() {
    initHUD();
}