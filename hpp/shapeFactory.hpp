#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include "factory.hpp"
#include "types.hpp"
#include "loaderMD2.hpp"

class shapeFactory: public factory, public singleton<shapeFactory> {
protected:
	virtual void * actualLoad(string fn);
	e_loc scale;
public:
	virtual void setScale(e_loc scale);
	shapeFactory();
	 
};

#endif