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
class colorRGB {
public:
	e_loc r,g,b;
};

/**
* Rozszerzenie colorRGB o kanał Alpha
*/
class colorRGBA : public colorRGB {
public:
	e_loc a;
};

struct coords {
	MathTypes::vector translation,rotation;
};

struct frustumSizes {
 e_loc x,y,znear,zfar;
};


struct uv {
 e_loc u,v;
};

typedef MathTypes::BasicVector v_type;
typedef MathTypes::BasicVector n_type;

struct frame {
	e_loc fnum,fval;
	v_type *verts;
};



#endif	/* TYPES_HPP */

