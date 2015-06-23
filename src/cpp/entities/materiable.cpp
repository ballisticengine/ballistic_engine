#include "entities/materiable.hpp"

Material *Materiable::getMaterial() {
 return this->mat;
}
void Materiable::setMaterial(Material *mat) {
 this->mat=mat;
}