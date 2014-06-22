
#ifndef TYPES_HPP
#define	TYPES_HPP
typedef float e_loc;

class vertex {
    e_loc x,y,z;
    bool operator=(const vertex &v);
};

class triangle {
    unsigned int n_triangles;
    vertex * vertices;
    bool operator=(const triangle &t);
};


#endif	/* TYPES_HPP */

