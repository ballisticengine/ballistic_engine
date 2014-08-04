#include "loader.hpp"

void * loader::get(string fn) {
	if(items.find(fn)==items.end()) {
	  items[fn]=this->actualLoad(fn);
	}
 return items[fn];
}