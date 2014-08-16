#include "facetexShape.hpp"

texTriangle::texTriangle(vertex *a,vertex *b,vertex *c) {
	 this->v[0] = a;
    this->v[1] = b;
    this->v[2] = c;
}

void texTriangle::setTexture(texture *tex) {
 this->tex=tex;
}

texture * texTriangle::getTexture() {
 return this->tex;
}