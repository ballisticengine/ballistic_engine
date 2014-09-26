#include "facetexShape.hpp"

texTriangle::texTriangle(vertex *a,vertex *b,vertex *c) {
	 this->v[0] = a;
    this->v[1] = b;
    this->v[2] = c;
}

void texPolyGeneral::setTexture(texture *tex) {
 this->tex=tex;
}

texture * texPolyGeneral::getTexture() {
 return this->tex;
}
texPoly::texPoly(vector<vertex *>vs) {
 this->v=vs;
}