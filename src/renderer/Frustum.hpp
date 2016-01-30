#ifndef FRUSTUM_HPP
#define	FRUSTUM_HPP

#include <cmath>

using namespace std;

#include "types/basic_typedefs.hpp"

class Frustum {
public:
    scalar_t left, right, bottom, top, near, far;
    
    Frustum();
    
    Frustum(scalar_t left, scalar_t right,
            scalar_t bottom, scalar_t top,
            scalar_t near, scalar_t far);
    
    scalar_t getWidth();
    scalar_t getHeight();
};

#endif	

