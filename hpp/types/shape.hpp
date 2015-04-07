
#ifndef SHAPE_HPP
#define	SHAPE_HPP

#include <vector>


using namespace std;

#include "types/mathTypes.hpp"
#include "types/types.hpp"
#include "types/material.hpp"

struct Face {
    unsigned int *index;
    Vector3d *normals;
    UV *uvs;
};

class ShapeAbstract {
public:
    Vector3d *vertices, *normals;
    Face *faces;
    UV *uvs;
    size_t v_count, uv_count, f_count, v_per_poly;
    virtual ~ShapeAbstract();
};

class Shape : public ShapeAbstract {
public:
    Shape();
    Texture **textures;
    Material **materials;
    size_t frame_count;
    Frame *frames;
    e_loc *frame_times;
    void *renderer_hint;
    virtual void calculateNormals();
    ~Shape();
};

typedef vector<Shape *> shape_list;

#endif	

