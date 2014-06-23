
#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>

using namespace std;

typedef float e_loc;

class vertex {
public:
    e_loc x, y, z;
    bool operator==(vertex &v);
    vertex();
    vertex(e_loc x,e_loc y,e_loc z);
    
};

class triangle {
public:
    vertex *v[3];
    bool operator==(triangle &t);
};

class shape {
    /*unsigned int n_tris;
    triangle * tris;
     * */
    vector <vertex *> tris;
public:
    bool operator==(shape &s);
    
    void addVertex(vertex *v);
    void addVertex(e_loc x,e_loc y,e_loc z);
    vertex * findVertex(vertex *v);
};


#endif	/* TYPES_HPP */

