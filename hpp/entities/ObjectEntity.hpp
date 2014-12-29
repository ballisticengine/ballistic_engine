#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entities/entity.hpp"
#include "entities/physicalEntity.hpp"
#include "types/texture.hpp"
#include "types/types.hpp" 
#include "types/material.hpp"
#include "types/facetexShape.hpp"
#include "types/boundingCube.hpp"


class ObjectEntity : public PhysicalEntity,public Texturable {
protected:
	
	
	
	Material *mat;
public:
	virtual faceTexShape * getModel();
	
	faceTexShape *model;
	virtual void setModel(faceTexShape *model);
	
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
	
	

};

#endif