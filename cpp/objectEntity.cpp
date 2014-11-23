#include "ObjectEntity.hpp"

faceTexShape * ObjectEntity::getModel() {
	return model;  
}

void ObjectEntity::setModel(faceTexShape *model) {
	this->model=model;
}


shape *ObjectEntity::getBoundingShape() {
	return this->bounding;
}

Material *ObjectEntity::getMaterial() {
 return this->mat;
}
void ObjectEntity::setMaterial(Material *mat) {
 this->mat=mat;
}