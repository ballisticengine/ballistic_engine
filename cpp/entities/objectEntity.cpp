#include "entities/ObjectEntity.hpp"

faceTexShape * ObjectEntity::getModel() {
	return model;  
}

void ObjectEntity::setModel(faceTexShape *model) {
	this->model=model;
}



Material *ObjectEntity::getMaterial() {
 return this->mat;
}
void ObjectEntity::setMaterial(Material *mat) {
 this->mat=mat;
}




