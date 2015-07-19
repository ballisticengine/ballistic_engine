#include "resources/ResourceManager.hpp"

ResourceManager::ResourceManager() {
    this->setWD("./data");
}

ResourceManager::~ResourceManager() {

}

void * ResourceManager::get(string file_name, LoaderType type) {
    //       string ext = Utils::getExt(fn);
    //    this->force_common = force_common;
    //    
    //    if (items.find(fn) == items.end() || clone) {
    //        string path;
    //
    //        if (fn[0] == '@' || force_common) {
    //            uses_common = true;
    //            string rfn;
    //            if (fn[0] == '@') {
    //                rfn = fn.substr(1, fn.size());
    //            } else {
    //                rfn = fn;
    //            }
    //            path = wd + DS + string(COMMON_DIR) + DS + getSubDir() + DS + rfn;
    //        } else {
    //            path = wd + DS + string(LVL_DIR) + DS + lvl + DS + getSubDir() + DS + fn;
    //            uses_common = false;
    //        }
    //        
    //        if(clone) {
    //            LoadedResource *p=this->actualLoad(path, fn);
    //            item_ptr.push_back(p);
    //        } else {
    //            items[fn] = this->actualLoad(path, fn);
    //            item_ptr.push_back(items[fn]);
    //        }
    //        
    //        items[fn]->resource->setFilename(path);
    //        items[fn]->resource->setOrigFilename(fn);
    //    }
    //    return items[fn]->object;



    Loader *loader = LibLoad::getInstance()->getLoaderByExtension(Utils::getExt(file_name), type);
    if (!loader) {
        return 0;
    }
    string path;
    if (items.find(file_name) == items.end()) {
        path = resolveFilename(file_name, loader->getType());
        void *resource = loader->load(path);
        dep_list dependencies = loader->getDependencies();
        for (size_t i = 0; i < dependencies.size(); i++) {
            cout << "Dependency " << dependencies[i].file_name << endl;
            dependencies[i].target=this->get(dependencies[i].file_name);
        }
        items[file_name] = resource;
        items_v.push_back(resource);
    }

    return items[file_name];
}

string ResourceManager::resolveFilename(string file_name, LoaderType type) {
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

string ResourceManager::getSubDir(LoaderType type) {
    string subdir;
    switch (type) {
        case TEXTURE:
            subdir = TEX_DIR;
            break;
        case SHAPE:
            subdir = MODEL_DIR;
            break;
        case LEVEL:
            subdir = LVL_DIR;
            break;
        default:
            subdir = "";
            break;
    }
    return subdir;
}

void ResourceManager::setWD(string wd) {
    this->wd = wd;
}

void ResourceManager::setLevel(string lvl) {
    this->lvl = lvl;
}

string ResourceManager::getWD() {
    return this->wd;
}

string ResourceManager::getLevel() {
    return this->lvl;
}