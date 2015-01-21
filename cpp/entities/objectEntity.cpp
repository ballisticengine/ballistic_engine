#include "entities/ObjectEntity.hpp"

shape * ObjectEntity::getModel() {
	return model;  
}

void ObjectEntity::setModel(shape *model) {
	this->model=model;
}



Material *ObjectEntity::getMaterial() {
 return this->mat;
}
void ObjectEntity::setMaterial(Material *mat) {
 this->mat=mat;
}




