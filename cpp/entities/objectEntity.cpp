#include "entities/ObjectEntity.hpp"

Shape * ObjectEntity::getModel() {
	return model;  
}

void ObjectEntity::setModel(Shape *model) {
	this->model=model;
}



Material *ObjectEntity::getMaterial() {
 return this->mat;
}
void ObjectEntity::setMaterial(Material *mat) {
 this->mat=mat;
}




