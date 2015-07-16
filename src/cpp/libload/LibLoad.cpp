#include "libload/LibLoad.hpp"

void LibLoad::error(string name) {
    cout << "Library " << name << " error: " << dlerror() << endl;
}

void LibLoad::discoverLoaders() {
    
}

Module LibLoad::loadLib(string file_name, string entry_point_name) {
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
    return module;
}

void LibLoad::registerModule(string name, string file_name, string entry_point_name) {
   
    Module module = loadLib(file_name, entry_point_name);
    libs[name] = module;
}

void * LibLoad::getModuleClass(string name) {
    return libs[name].module_class;
}

LibLoad::~LibLoad() {
    for(lib_map::iterator i=libs.begin(); i!=libs.end(); i++) {
        dlclose(i->second.handle);
    }
}