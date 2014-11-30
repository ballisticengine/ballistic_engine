#ifndef BOUNDING_CUBE_H
#define BOUNDING_CUBE_H

#include "types.hpp"
#include "mathTypes.hpp"

class BoundingCube {
protected:
	e_loc width,height,depth;
public:
	BoundingCube();
	BoundingCube(shape *s);
	BoundingCube(e_loc width,e_loc height,e_loc depth);
	void calculate(shape *s);
	e_loc toSphereRadius();
	void print();
	e_loc getWidth();
	e_loc getHeight();
	e_loc getDepth();
	//e_loc max_x,min_x,max_y,min_y,max_z,min_z;
	MathTypes::vector max,min;


};

#endif
