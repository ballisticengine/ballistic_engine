#ifndef BOUNDING_CUBE_H
#define BOUNDING_CUBE_H

#include "types/types.hpp"

#include "types/mathTypes.hpp"
#include "types/shape.hpp"
#include <vector>


class BoundingCube {
protected:
	
public:
	e_loc width,height,depth;
	BoundingCube();
	BoundingCube(shape *s);
	BoundingCube(e_loc width,e_loc height,e_loc depth);
	BoundingCube(e_loc minx,e_loc miny,e_loc minz,e_loc maxx,e_loc maxy,e_loc maxz);
	void calculateSizes();
	void calculate(shape *s);
	e_loc toSphereRadius();
	void print();
	e_loc getWidth();
	e_loc getHeight();
	e_loc getDepth();
        string name;
	//e_loc max_x,min_x,max_y,min_y,max_z,min_z;
	MathTypes::vector max,min,loc;


};

typedef vector<BoundingCube *> bounding_list;

#endif
