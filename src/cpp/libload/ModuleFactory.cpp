#include "libload/ModuleFactory.hpp"

void ModuleFactory::error(string name) {
    cout << "Library " << name << " error: " << dlerror() << endl;
}

RendererAbstract * ModuleFactory::getRenderer(string name) {
    string file_name = "./bin/" + name + ".so";
    lib_handle h = this->load(file_name);
    if (!h) {
        error(name + " file ");
    }
    typedef void* (*renderer_f)();
    
    renderer_f fn;


    fn = (renderer_f) dlsym(h, "returnRenderer");
    if (!fn) {
        error(name + " function ");
    }

    return (RendererAbstract *) fn();
}

lib_handle ModuleFactory::load(string fn) {
    lib_handle h = dlopen(fn.c_str(), RTLD_NOW | RTLD_GLOBAL);
}

ModuleFactory::~ModuleFactory() {
    for (size_t i = 0; i < libs.size(); i++) {
        dlclose(libs[i]);
    }
}