#include "entities/physicalEntity.hpp"



Coords PhysicalEntity::nextCoords(time_int diff) {
   

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

void PhysicalEntity::setIfNotZero(e_loc &a, e_loc &b) {
    if (a != 0) {
        b = a;
    }
}

void PhysicalEntity::changeVelocity(Coords velocity) {
    setIfNotZero(velocity.translation.x, this->velocity.translation.x);
    setIfNotZero(velocity.translation.y, this->velocity.translation.y);
    setIfNotZero(velocity.translation.z, this->velocity.translation.z);
    setIfNotZero(velocity.rotation.x, this->velocity.rotation.x);
    setIfNotZero(velocity.rotation.y, this->velocity.rotation.y);
    setIfNotZero(velocity.rotation.z, this->velocity.rotation.z);
    //this->velocity=velocity;

}

void PhysicalEntity::setVelocity(Coords velocity) {

    this->velocity = velocity;

}

Coords PhysicalEntity::getVelocity() {

    return this->velocity;
}

void PhysicalEntity::printVelocity() {
    cout << "T: " << velocity.translation.x << ", " << velocity.translation.y << ", " << velocity.translation.z << endl;
    cout << "R: " << velocity.rotation.x << ", " << velocity.rotation.y << ", " << velocity.rotation.z << endl;
}

PhysicalEntity::PhysicalEntity() {
    this->velocity.reset();
    this->acceleration.reset();
    this->no_physics=false;
}