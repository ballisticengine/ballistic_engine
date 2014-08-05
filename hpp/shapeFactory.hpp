#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include "factory.hpp"
#include "types.hpp"
#include "loaderMD2.hpp"

class shapeFactory: public factory<shape,shapeFactory> {
protected:
	shape * actualLoad(string fn);
public:
	 
};

#endif