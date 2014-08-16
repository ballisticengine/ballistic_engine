#include "factory.hpp"

void * factory::get(string fn) {
	if(items.find(fn)==items.end()) {
	  items[fn]=this->actualLoad(wd+DS+fn);
	  item_ptr.push_back(items[fn]);
	}
 return items[fn];
}

factory::~factory() {
 cout << "Cleaning up" << endl;
 for(int i=0; i<item_ptr.size(); i++) {
	//delete item_ptr[i];
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
  wd=".";
 }

 void factory::setWD(string wd) {
  this->wd=wd;
 }