#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entity.hpp"
#include "physicalEntity.hpp"
#include "texture.hpp"
#include "types.hpp" 
#include "material.hpp"

class ObjectEntity : public PhysicalEntity,public Texturable {
protected:
	shape *model,*bounding;
	texture *tex;
	Material *mat;
public:
	virtual shape * getModel();
	
	
	virtual void setModel(shape *model);
	
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
	virtual shape *getBoundingShape();

};

#endif