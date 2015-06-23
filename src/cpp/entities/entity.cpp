#include "entities/entity.hpp"

Coords Entity::getCoords() {
    Coords c;
    c.translation.x = x;
    c.translation.y = y;
    c.translation.z = z;
    c.rotation.x = rx;
    c.rotation.y = ry;
    c.rotation.z = rz;
    return c;
}

void Entity::rotate(e_loc x, e_loc y, e_loc z) {
    this->rx += x;
    this->ry += y;
    this->rz += z;

}

void Entity::translate3(e_loc x, e_loc y, e_loc z) {
    this->translate(x, y, z);

}

void Entity::translate(e_loc x, e_loc y, e_loc z) {

    this->x += x;
    this->y += y;
    this->z += z;
//    for (size_t i = 0; i < boundings.size(); i++) {
//        boundings[i]->max.x -= x;
//        boundings[i]->max.y -= y;
//        boundings[i]->max.z -= z;
//        boundings[i]->min.x -= x;
//        boundings[i]->min.y -= y;
//        boundings[i]->min.z -= z;
//        boundings[i]->loc.x = this->x;
//        boundings[i]->loc.y = this->y;
//        boundings[i]->loc.z = this->z;
//    }

}

void Entity::locate(e_loc x, e_loc y, e_loc z) {
    this->x = x;
    this->y = y;
    this->z = z;
//    for (size_t i = 0; i < boundings.size(); i++) {
//        boundings[i]->max.x -= x;
//        boundings[i]->max.y -= y;
//        boundings[i]->max.z -= z;
//        boundings[i]->min.x -= x;
//        boundings[i]->min.y -= y;
//        boundings[i]->min.z -= z;
//        boundings[i]->loc.x = this->x;
//        boundings[i]->loc.y = this->y;
//        boundings[i]->loc.z = this->z;
//    }
}

void Entity::syncBounding() {

}

void Entity::face(e_loc x, e_loc y, e_loc z) {
    this->rx = x;
    this->ry = y;
    this->rz = z;
}

void Entity::translate(Coords c) {
    this->translate(c.translation.x, c.translation.y, c.translation.z);
}

Entity::Entity() {
    parent=0;
    no_collisions = false;
}

Entity::~Entity() {
    cout << "Destroying entity" << endl;
    //if (this->bounding_box) {
    //delete this->bounding_box;
    //}
}

void Entity::addBoundingBox(BoundingCube *box) {
    BoundingCube *bounding_box = box;
    bounding_box->max.x -= x;
    bounding_box->max.y -= y;
    bounding_box->max.z -= z;

    bounding_box->min.x -= x;
    bounding_box->min.y -= y;
    bounding_box->min.z -= z;
    boundings.push_back(bounding_box);
}

BoundingCube * Entity::getBoundingBox() {
    if (boundings.size() > 0) {
        return boundings[0];
    } else {
        return 0;
    }
}

void Entity::makeBoundingBox() {
    ///
}

BoundingCube offsetBounding(BoundingCube *bc, Coords offset) {
    BoundingCube bcr;
    bcr = *bc;
    bcr.max = bcr.max + offset.translation;
    bcr.min = bcr.min + offset.translation;
    return bcr;
}

