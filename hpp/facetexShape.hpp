#ifndef FACETEX_SHAPE_H
#define FACETEX_SHAPE_H

/*
Reprezentuje kszta³t z teksturami przypisanymi do wielok¹tów
*/

#include "types.hpp"
#include "texture.hpp"

class texTriangle : public triangle {
public:
		texture *tex;
		texTriangle(vertex *a,vertex *b,vertex *c);
};



class faceTexShape : public shape {
protected:
	vector <texTriangle *> triangles;
};

#endif