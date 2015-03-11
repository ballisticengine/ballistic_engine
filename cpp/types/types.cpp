#include "types/types.hpp"



void Coords::reset() {
    translation.x =  translation.z = rotation.x = rotation.y = rotation.z = 0; //t.y =
}

Coords::Coords() {
    this->reset();
}