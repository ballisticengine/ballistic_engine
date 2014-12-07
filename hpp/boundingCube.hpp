#ifndef BOUNDING_CUBE_H
#define BOUNDING_CUBE_H

#include "types.hpp"
#include "mathTypes.hpp"
#include "vector"


class BoundingCube {
protected:
	e_loc width,height,depth;
public:
	BoundingCube();
	BoundingCube(shape *s);
	BoundingCube(poly *p);
	BoundingCube(e_loc width,e_loc height,e_loc depth);
	BoundingCube(e_loc minx,e_loc miny,e_loc minz,e_loc maxx,e_loc maxy,e_loc maxz);
	void calculate(vert_list s);
	e_loc toSphereRadius();
	void print();
	e_loc getWidth();
	e_loc getHeight();
	e_loc getDepth();
	//e_loc max_x,min_x,max_y,min_y,max_z,min_z;
	MathTypes::vector max,min;


};

typedef vector<BoundingCube *> bounding_list;

#endif
