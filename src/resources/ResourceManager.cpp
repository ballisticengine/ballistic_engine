#include "resources/ResourceManager.hpp"

ResourceManager::ResourceManager() {
    this->setWD("./data");
}

ResourceManager::~ResourceManager() {

}

factory_items_vector ResourceManager::getByType(ResourceType type = NONE) {
    factory_items_vector type_items;
    if (type != NONE) {
        for (size_t i = 0; i < items_v.size(); i++) {
            if (items_v[i]->type == type) {
                type_items.push_back(items_v[i]);
            }
        }
    } else {
        type_items = items_v;
    }

    return type_items;
}

void ResourceManager::resolveDependencies(Loader *loader) {
    dep_list dependencies = loader->getDependencies();
    for (size_t i = 0; i < dependencies.size(); i++) {
        //cout << "Dependency " << dependencies[i].file_name << endl;
        *dependencies[i].target = this->get(dependencies[i].file_name, dependencies[i].type);
    }
    loader->cleanDependencies();
}

void ResourceManager::resolveAllDependencies() {
    lib_vector libs = LibLoad::getInstance()->getAllLoaders();

    for (size_t i=0; i < libs.size(); i++) {
        Loader *loader = (Loader *)libs[i].module_class; 
        resolveDependencies(loader);
    }
}

void * ResourceManager::get(string file_name, ResourceType type) {

    Loader *loader = (Loader *)LibLoad::getInstance()->getLoaderByExtension(Utils::getExt(file_name), type);
    if (!loader) {
        return 0;
    }
    string path;
    if (items.find(file_name) == items.end()) {
        path = resolveFilename(file_name, loader->getType());
        LoadedResource *resource = new LoadedResource();
        resource->object = loader->load(path);
        resource->type = loader->getType();
        if (!resource) {
            throw ResourceNotFound(file_name);
        }
        resolveDependencies(loader);
        
        Resource *resinfo=new Resource;
        resinfo->setOrigFilename(file_name);
        resinfo->setFilename(path);
        resmap[resource->object]=resinfo;
        
        items[file_name] = resource;
        items_v.push_back(resource);
    }

    return items[file_name]->object;
}

Resource * ResourceManager::getResource(void *object) {
    return resmap[object];
}

string ResourceManager::resolveFilename(string file_name, ResourceType type) {
    string path, subdir = getSubDir(type);
    if (subdir != "") {
        subdir = getSubDir(type) + DS;
    }
    if (file_name[0] == '@') {
        string rewritten_fn = file_name.substr(1, file_name.size());
        path = wd + DS + string(COMMON_DIR) + DS + subdir + rewritten_fn;
    } else {
        path = wd + DS + string(LVL_DIR) + DS + lvl + DS + subdir + file_name;
    }
    return path;
}

string ResourceManager::getSubDir(ResourceType type) {
    string subdir;
    switch (type) {
        case TEXTURE:
            subdir = TEX_DIR;
            break;
        case SHAPE:
            subdir = MODEL_DIR;
            break;
//        case LEVEL:
//            subdir = LVL_DIR;
//            break;
        default:
            subdir = "";
            break;
    }
    return subdir;
}


void ResourceManager::setLevel(string lvl) {
    this->lvl = lvl;
}

string ResourceManager::getLevel() {
    return this->lvl;
}