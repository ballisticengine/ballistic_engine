#ifndef FRUSTUM_HPP
#define	FRUSTUM_HPP

#include <cmath>

using namespace std;

#include "types/basic_typedefs.hpp"

class Frustum {
public:
    e_loc left, right, bottom, top, near, far;
    
    Frustum();
    
    Frustum(e_loc left, e_loc right,
            e_loc bottom, e_loc top,
            e_loc near, e_loc far);
    
    e_loc getWidth();
    e_loc getHeight();
};

#endif	
