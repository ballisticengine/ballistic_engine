#include "physicalEntity.hpp"

coords PhysicalEntity::nextCoords(time_int diff) {
 coords c;
 return c;
}

void PhysicalEntity::setVelocity(TrRot velocity) {
	this->velocity=velocity;
}

TrRot PhysicalEntity::getVelocity() {
	
	return this->velocity;
}