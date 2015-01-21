
#ifndef SHAPE_HPP
#define	SHAPE_HPP

#include <vector>


using namespace std;

#include "types/mathTypes.hpp"
#include "types/types.hpp"
#include "types/material.hpp"




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
        Material **materials;
	
	size_t frame_count;
	frame *frames;
	e_loc *frame_times;
	void *renderer_hint;
	
	virtual void calculateNormals();
    
     ~shape();
};

typedef vector<shape *> shape_list;

#endif	

