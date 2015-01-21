#include "entities/physicalEntity.hpp"

void TrRot::reset() {
    t.x =  t.z = r.x = r.y = r.z = 0; //t.y =
}

TrRot::TrRot() {
    this->reset();
}

coords PhysicalEntity::nextCoords(time_int diff) {
   

    coords c;
    //cout << diff < endl;
    c.translation.x = velocity.t.x*diff;
    c.translation.y = velocity.t.y*diff;
    c.translation.z = velocity.t.z*diff;
    c.rotation.x = velocity.r.x*diff;
    c.rotation.y = velocity.r.y*diff;
    c.rotation.z = velocity.r.z*diff;
     if (acceleration.t.x) {
        velocity.t.x+=acceleration.t.x*diff;
    }
    if (acceleration.t.y) { 
        velocity.t.y+=acceleration.t.y*diff;
    }
    if (acceleration.t.z) {
        velocity.t.z+=acceleration.t.z*diff;
    }
    return c;
}

void PhysicalEntity::setIfNotZero(e_loc &a, e_loc &b) {
    if (a != 0) {
        b = a;
    }
}

void PhysicalEntity::changeVelocity(TrRot velocity) {
    setIfNotZero(velocity.t.x, this->velocity.t.x);
    setIfNotZero(velocity.t.y, this->velocity.t.y);
    setIfNotZero(velocity.t.z, this->velocity.t.z);
    setIfNotZero(velocity.r.x, this->velocity.r.x);
    setIfNotZero(velocity.r.y, this->velocity.r.y);
    setIfNotZero(velocity.r.z, this->velocity.r.z);
    //this->velocity=velocity;

}

void PhysicalEntity::setVelocity(TrRot velocity) {

    this->velocity = velocity;

}

TrRot PhysicalEntity::getVelocity() {

    return this->velocity;
}

void PhysicalEntity::printVelocity() {
    cout << "T: " << velocity.t.x << ", " << velocity.t.y << ", " << velocity.t.z << endl;
    cout << "R: " << velocity.r.x << ", " << velocity.r.y << ", " << velocity.r.z << endl;
}

PhysicalEntity::PhysicalEntity() {
    this->velocity.reset();
    this->acceleration.reset();
    this->no_physics=false;
}