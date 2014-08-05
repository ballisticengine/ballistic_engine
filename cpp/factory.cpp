#include "factory.hpp"

void * factory::get(string fn) {
	if(items.find(fn)==items.end()) {
	  items[fn]=this->actualLoad(fn);
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