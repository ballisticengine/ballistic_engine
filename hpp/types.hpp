
#ifndef TYPES_HPP
#define	TYPES_HPP
typedef float e_loc;

struct vertex {
    e_loc x,y,z;
    
};

struct triangle {
    unsigned int n_triangles;
    vertex * vertices;
};


#endif	/* TYPES_HPP */

