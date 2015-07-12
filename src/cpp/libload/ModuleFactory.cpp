#include "libload/ModuleFactory.hpp"

void ModuleFactory::error(string name) {
    cout << "Library " << name << " error: " << dlerror() << endl;
}

void ModuleFactory::registerModule(string name, string file_name, string entry_point_name) {
    Module module;
    module.entry_point_name = entry_point_name;
    module.file_name = file_name;

    string full_file_name = "./bin/" + file_name + ".so";
    module.handle = dlopen(full_file_name.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!module.handle) {
        error(module.file_name + " file ");
    }
    typedef void* (*module_f)();

    module_f fn = (module_f) dlsym(module.handle, entry_point_name.c_str());

    if (!fn) {
        error(entry_point_name + " function ");
    }

    module.module_class=(void *)fn();
    
    libs[name] = module;
}

void * ModuleFactory::getModuleClass(string name) {
    return libs[name].module_class;
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
    //    for (size_t i = 0; i < libs.size(); i++) {
    //        dlclose(libs[i]);
    //    }
    for(lib_map::iterator i=libs.begin(); i!=libs.end(); i++) {
        //Module m=*i;
        //dlclose(m.handle);
    }
}