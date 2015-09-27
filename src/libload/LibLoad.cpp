#include "libload/LibLoad.hpp"

void LibLoad::error(string name) {
    cout << "Library " << name << " error: " << dlerror() << endl;
}

void LibLoad::registerLoader(string file_name) {

    loads.push_back(loadLib(file_name, "returnLoader"));
}

void * LibLoad::getLoaderByExtension(string ext, ResourceType type) {
    for (size_t i = 0; i < loads.size(); i++) {
        Loader * loader = (Loader *) loads[i].module_class;

        if (loader->handlesEntension(ext) && (loader->getType() == type || type == NONE)) {

            return loads[i].module_class;
        }
    }
    return 0;
}

void LibLoad::discoverLoaders() {
    cout << "Discovering loaders..." << endl;
    fs::path l_path(this->wd + "/loaders");
    fs::directory_iterator end_itr;
    for (fs::directory_iterator itr(l_path); itr != end_itr; ++itr) {
        cout << "Registering " << itr->path().string() << endl;
        this->registerLoader(itr->path().string());
    }
}

lib_vector & LibLoad::getAllLoaders() {
    return this->loads;
}

Module LibLoad::loadLib(string file_name, string entry_point_name) {
    Module module;
    module.entry_point_name = entry_point_name;
    module.file_name = file_name;

    string full_file_name = file_name;
    module.handle = dlopen(full_file_name.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!module.handle) {
        error(module.file_name + " file ");
    }
    typedef void* (*module_f)();

    module_f fn = (module_f) dlsym(module.handle, entry_point_name.c_str());

    if (!fn) {
        error(entry_point_name + " function ");
    }

    module.module_class = (void *) fn();
    return module;
}

void LibLoad::registerModule(string name, string file_name, string entry_point_name) {

    Module module = loadLib(this->wd + "/" + file_name + ".so", entry_point_name);
    libs[name] = module;
}

void * LibLoad::getModuleClass(string name) {
    return libs[name].module_class;
}

LibLoad::~LibLoad() {
    for (lib_map::iterator i = libs.begin(); i != libs.end(); i++) {
        dlclose(i->second.handle);
    }
}