/**
* Zestaw klas definujący podstawowe typy używane przez silnik, nie uwzględnia struktur matematycznych (wektory,macierze), które
* obsugiwane są w klasach zawartych w mathTypes.hpp
*/

#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>

#include "mathTypes.hpp"
#include "texture.hpp"

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

class shape {
	e_loc scale;
	
	
public:
    void *renderer_hint;
	virtual void setRendererHint(void *hint);
	virtual void * getRendererHint();
	texture **textures;
	size_t v_count,uv_count,f_count,v_per_poly;
	size_t frame_count;
	frame *frames;
	e_loc *frame_times;
	MathTypes::BasicVector *vertices,*normals;
	uv *uvs;
	size_t **faces;


	virtual void setVertices(v_type *vs,size_t count);
	/* Ilość normalnych = ilość wierchołków */
	virtual void setNormals(n_type *normals);
	virtual void setUvs(uv *uvs,size_t count);
	virtual void calculateNormals();
	
    virtual void setScale(e_loc scale);
	virtual e_loc getScale();
 
    
     ~shape();
};

typedef vector<shape *> shape_list;

#endif	/* TYPES_HPP */

