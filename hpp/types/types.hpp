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

class ShapeAbstract {
public:
	
	MathTypes::BasicVector *vertices,*normals;
	uv *uvs;
	unsigned int **faces;
	size_t v_count,uv_count,f_count,v_per_poly;
	virtual ~ShapeAbstract();
};


class shape : public ShapeAbstract {

public:
    shape();
	texture **textures;
	
	size_t frame_count;
	frame *frames;
	e_loc *frame_times;
	void *renderer_hint;
	
	virtual void calculateNormals();
    
     ~shape();
};

typedef vector<shape *> shape_list;

#endif	/* TYPES_HPP */

