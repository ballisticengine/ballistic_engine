#include "factories/factory.hpp"

 LoadedResource::LoadedResource(void *object, Resource *resource) : object(object), resource(resource) {
     
 }

void Factory::abort(string reason) {
    if (reason!="") {
        cout << reason << endl;
    }
    cout << "Aborting..." << endl;
    exit(1);   
}


 
void * Factory::get(string fn, bool force_common,bool clone) {
    this->force_common = force_common;
    
    if (items.find(fn) == items.end() || clone) {
        string path;

        if (fn[0] == '@' || force_common) {
            uses_common = true;
            string rfn;
            if (fn[0] == '@') {
                rfn = fn.substr(1, fn.size());
            } else {
                rfn = fn;
            }
            path = wd + DS + string(COMMON_DIR) + DS + getSubDir() + DS + rfn;
        } else {
            path = wd + DS + string(LVL_DIR) + DS + lvl + DS + getSubDir() + DS + fn;
            uses_common = false;
        }
        
        if(clone) {
            LoadedResource *p=this->actualLoad(path, fn);
            item_ptr.push_back(p);
        } else {
            items[fn] = this->actualLoad(path, fn);
            item_ptr.push_back(items[fn]);
        }
        
        items[fn]->resource->setFilename(path);
        items[fn]->resource->setOrigFilename(fn);
    }
    return items[fn]->object;
}

Factory::~Factory() {
    cout << "Cleaning up" << endl;
    for (int i = 0; i < item_ptr.size(); i++) {
        delete item_ptr[i];
    }
}

vector <LoadedResource *> Factory::getAll() {
    return this->item_ptr;
}


Factory::Factory() {
    wd = "./data";

}

void Factory::setWD(string wd) {
    this->wd = wd;
}

void Factory::setLevel(string lvl) {
    this->lvl = lvl;
}