/**
* Zestaw klas definujący podstawowe typy używane przez silnik, nie uwzględnia struktur matematycznych (wektory,macierze), które
* obsugiwane są w klasach zawartych w mathTypes.hpp
*/

#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>

#include "types/mathTypes.hpp"
#include "types/texture.hpp"


using namespace std;


/**
* Pomocnicza klasa reprezentująca kolor RGB
*/

class ColorRGB {
public:
	e_loc r,g,b;
};

/**
* Rozszerzenie colorRGB o kanał Alpha
*/
class ColorRGBA : public ColorRGB {
public:
	e_loc a;
};

class Coords {
public:	
        Vector3d translation,rotation;
        void reset();
	Coords();
};

struct FrustumSizes {
 e_loc x,y,znear,zfar;
};


struct UV {
 e_loc u,v;
};

typedef BasicVector v_type;
typedef BasicVector n_type;

struct Frame {
	e_loc fnum,fval;
	v_type *verts;
};



#endif	/* TYPES_HPP */

