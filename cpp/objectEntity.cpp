#include "objectEntity.hpp"

shape * objectEntity::getModel() {
	return model;  
}

void objectEntity::setModel(shape *model) {
	this->model=model;
}

void objectEntity::setTexture(texture *tex) {
 this->tex=tex;
}

texture *objectEntity::getTexture() {
 return this->tex;
}
