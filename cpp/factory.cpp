#include "factory.hpp"

template <typename T,typename S> T * factory<T,S>::get(string fn) {
	if(items.find(fn)==items.end()) {
	  items[fn]=this->actualLoad(fn);
	}
 return items[fn];
}