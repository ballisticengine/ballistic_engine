#include "factories/factory.hpp"

void * factory::get(string fn) {
	if(items.find(fn)==items.end()) {
            string path;
            if(fn[0]=='@') {
                string rfn=fn.substr(1,fn.size());
                path=wd+DS+string(COMMON_DIR)+DS+getSubDir()+DS+rfn;
            } else {
            path=wd+DS+string(LVL_DIR)+DS+lvl+DS+getSubDir()+DS+fn;
            }
            cout << "Factory: " << path << endl;
            cout.flush();
            items[fn]=this->actualLoad(path);
	  item_ptr.push_back(items[fn]);
	}
 return items[fn];
}

factory::~factory() {
 cout << "Cleaning up" << endl;
 for(int i=0; i<item_ptr.size(); i++) {
	delete item_ptr[i];
 }
}

vector <void *> factory::getAll() {
	return this->item_ptr;
}

string factory::getExt(string fn) {
	size_t dotpos=fn.find_last_of(".");
	string ext=fn.substr(dotpos+1,fn.size());
	return ext;
}

 factory::factory() {
  wd="./data";

 }

 void factory::setWD(string wd) {
  this->wd=wd;
 }
 
 void factory::setLevel(string lvl) {
     this->lvl=lvl;
 }