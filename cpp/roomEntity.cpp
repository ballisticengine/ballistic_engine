#include "roomEntity.hpp"


roomEntity::roomEntity() {

}
	
shape *roomEntity::getBoundingShape() {
	return this->model;
}