#ifndef FACETEX_SHAPE_H
#define FACETEX_SHAPE_H

/*
Reprezentuje kszta³t z teksturami przypisanymi do wielok¹tów
*/

#include "types.hpp"
#include "texture.hpp"

class texPolyGeneral {
protected:
		texture *tex;
public:
	void setTexture(texture *tex);
	texture * getTexture();
};

class texTriangle : public triangle,public texPolyGeneral {

public:
	
		texTriangle(vertex *a,vertex *b,vertex *c);
		
};


class texPoly : public poly,public texPolyGeneral {
public:
	texPoly(vector<vertex *>vs);
};


class faceTexShape : public shape {
protected:
	vector <texTriangle *> triangles;
};

#endif