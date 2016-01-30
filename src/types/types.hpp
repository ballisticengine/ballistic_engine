/**
* Zestaw klas definujący podstawowe typy używane przez silnik, nie uwzględnia struktur matematycznych (wektory,macierze), które
* obsugiwane są w klasach zawartych w Vector3d.hpp
*/

#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>

#include "types/Vector3d.hpp"
#include "types/texture.hpp"



using namespace std;


class ColorRGB {
public:
    ColorRGB() {};
    ColorRGB(unsigned int i);
    ColorRGB(scalar_t r, scalar_t g,scalar_t b);
    scalar_t r,g,b;
    bool operator==(const ColorRGB &color);
};


class ColorRGBA : public ColorRGB {
public:
    ColorRGBA() {};
    ColorRGBA(unsigned int i);
    ColorRGBA(scalar_t r, scalar_t g,scalar_t b, scalar_t a);
    bool operator==(const ColorRGBA &color);
    scalar_t a;
};

class Coords {
public:	
        Vector3d translation,rotation;
        void reset();
	Coords();
};

struct FrustumSizes {
 scalar_t x,y,znear,zfar;
};


struct UV {
 scalar_t u,v;
};

typedef Vector3d v_type;
typedef Vector3d n_type;

struct Frame {
	scalar_t fnum,fval;
	v_type *verts;
};



#endif	/* TYPES_HPP */

