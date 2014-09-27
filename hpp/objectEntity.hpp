#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entity.hpp"
#include "physicalEntity.hpp"
#include "texture.hpp"
#include "types.hpp" 

class objectEntity : public PhysicalEntity {
protected:
	shape *model;
	texture *tex;
public:
	virtual shape * getModel();
	virtual texture *getTexture();
	virtual void setModel(shape *model);
	virtual void setTexture(texture *tex);

};

#endif