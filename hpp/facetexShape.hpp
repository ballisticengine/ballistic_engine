#ifndef FACETEX_SHAPE_H
#define FACETEX_SHAPE_H

/*
Reprezentuje kszta³t z teksturami przypisanymi do wielok¹tów
*/

#include "types.hpp"
#include "texture.hpp"

class texTriangle : public triangle {
protected:
		texture *tex;
public:
	
		texTriangle(vertex *a,vertex *b,vertex *c);
		void setTexture(texture *tex);
		texture * getTexture();
};



class faceTexShape : public shape {
protected:
	vector <texTriangle *> triangles;
};

#endif