#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "types/types.hpp"
#include "types/shape.hpp"

class Shape2d : public ShapeAbstract {
public:
	Shape2d(e_loc width,e_loc height);
};

#endif