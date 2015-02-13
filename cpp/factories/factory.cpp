#include "factories/factory.hpp"

void * factory::get(string fn, bool force_common,bool clone) {
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
        //cout << "Factory: " << path << endl;
        //cout.flush();
        if(clone) {
            void *p=this->actualLoad(path);
            item_ptr.push_back(p);
        } else {
            items[fn] = this->actualLoad(path);
            item_ptr.push_back(items[fn]);
        }
    }
    return items[fn];
}

factory::~factory() {
    cout << "Cleaning up" << endl;
    for (int i = 0; i < item_ptr.size(); i++) {
        delete item_ptr[i];
    }
}

vector <void *> factory::getAll() {
    return this->item_ptr;
}


factory::factory() {
    wd = "./data";

}

void factory::setWD(string wd) {
    this->wd = wd;
}

void factory::setLevel(string lvl) {
    this->lvl = lvl;
}