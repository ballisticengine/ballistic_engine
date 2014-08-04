#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entity.hpp"
#include "types.hpp" 

class objectEntity : public entity {
protected:
	shape *model;
public:
	shape * getModel();
	void setModel(shape *model);
};

#endif