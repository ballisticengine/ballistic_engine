#include "entities/texturable.hpp"

void Texturable::setTexture(Ballistic::Types::Texture *tex) {
 this->tex=tex;
}

Ballistic::Types::Texture * Texturable::getTexture() {
 return this->tex;
}

//////


