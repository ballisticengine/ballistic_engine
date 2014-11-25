#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entity.hpp"
#include "physicalEntity.hpp"
#include "texture.hpp"
#include "types.hpp" 
#include "material.hpp"
#include "facetexShape.hpp"

class ObjectEntity : public PhysicalEntity,public Texturable {
protected:
	faceTexShape *model;
	shape *bounding;
	texture *tex;
	Material *mat;
public:
	virtual faceTexShape * getModel();
	
	
	virtual void setModel(faceTexShape *model);
	
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
	virtual shape *getBoundingShape();

};

#endif