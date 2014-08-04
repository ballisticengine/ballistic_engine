#include "objectEntity.hpp"

shape * objectEntity::getModel() {
	return model;  
}

void objectEntity::setModel(shape *model) {
	this->model=model;
}