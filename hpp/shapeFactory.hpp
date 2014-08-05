#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include "factory.hpp"
#include "types.hpp"
#include "loaderMD2.hpp"

class shapeFactory: public factory, public singleton<shapeFactory> {
protected:
	virtual void * actualLoad(string fn);
public:
	 
};

#endif