#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include "factory.hpp"
#include "types.hpp"
#include "loaderMD2.hpp"

class shapeFactory: public factory {
protected:
	void * actualLoad(string fn);
public:
	 
};

#endif