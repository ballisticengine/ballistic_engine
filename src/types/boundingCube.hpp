#ifndef BOUNDING_CUBE_H
#define BOUNDING_CUBE_H

#include "types/types.hpp"

#include "types/Vector3d.hpp"
#include "types/shape.hpp"
#include <vector>
#include <string>

class BoundingCube {
protected:
	
public:
        
        scalar_t width,height,depth;
	BoundingCube();
	BoundingCube(Shape *s);
	BoundingCube(scalar_t width,scalar_t height,scalar_t depth);
	BoundingCube(scalar_t minx,scalar_t miny,scalar_t minz,scalar_t maxx,scalar_t maxy,scalar_t maxz);
	
        void rotate(scalar_t x,scalar_t y,scalar_t z);
        void calculateSizes();
	void calculate(Shape *s);
	scalar_t toSphereRadius();
	void print();
	scalar_t getWidth();
	scalar_t getHeight();
	scalar_t getDepth();
        string name;
	//scalar_t max_x,min_x,max_y,min_y,max_z,min_z;
	Vector3d max,min,loc;


};

typedef vector<BoundingCube *> bounding_list;

#endif
