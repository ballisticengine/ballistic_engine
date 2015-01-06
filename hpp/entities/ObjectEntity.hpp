#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entities/entity.hpp"
#include "entities/physicalEntity.hpp"
#include "types/texture.hpp"
#include "types/types.hpp" 
#include "types/material.hpp"
#include "types/shape.hpp"
#include "types/boundingCube.hpp"


class ObjectEntity : public PhysicalEntity,public Texturable {
protected:
	
	
	
	Material *mat;
public:
	virtual shape * getModel();
	
	shape *model;
	virtual void setModel(shape *model);
	
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
	
	

};

#endif