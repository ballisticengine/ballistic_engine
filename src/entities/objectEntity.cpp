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

Coords ObjectEntity::nextCoords(time_int diff) {
    Coords c;
    //cout << diff < endl;
    c.translation.x = velocity.translation.x*diff;
    c.translation.y = velocity.translation.y*diff;
    c.translation.z = velocity.translation.z*diff;
    c.rotation.x = velocity.rotation.x*diff;
    c.rotation.y = velocity.rotation.y*diff;
    c.rotation.z = velocity.rotation.z*diff;
     if (acceleration.translation.x) {
        velocity.translation.x+=acceleration.translation.x*diff;
    }
    if (acceleration.translation.y) { 
        velocity.translation.y+=acceleration.translation.y*diff;
    }
    if (acceleration.translation.z) {
        velocity.translation.z+=acceleration.translation.z*diff;
    }
    return c;
}

void ObjectEntity::setIfNotZero(e_loc &a, e_loc &b) {
    if (a != 0) {
        b = a;
    }
}

void ObjectEntity::changeVelocity(Coords velocity) {
    setIfNotZero(velocity.translation.x, this->velocity.translation.x);
    setIfNotZero(velocity.translation.y, this->velocity.translation.y);
    setIfNotZero(velocity.translation.z, this->velocity.translation.z);
    setIfNotZero(velocity.rotation.x, this->velocity.rotation.x);
    setIfNotZero(velocity.rotation.y, this->velocity.rotation.y);
    setIfNotZero(velocity.rotation.z, this->velocity.rotation.z);
    //this->velocity=velocity;

}

void ObjectEntity::setVelocity(Coords velocity) {

    this->velocity = velocity;

}

Coords ObjectEntity::getVelocity() {

    return this->velocity;
}

void ObjectEntity::printVelocity() {
    cout << "T: " << velocity.translation.x << ", " << velocity.translation.y << ", " << velocity.translation.z << endl;
    cout << "R: " << velocity.rotation.x << ", " << velocity.rotation.y << ", " << velocity.rotation.z << endl;
}

ObjectEntity::ObjectEntity() {
    this->velocity.reset();
    this->acceleration.reset();
    this->no_physics=false;
}


