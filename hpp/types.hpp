
#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>


using namespace std;

typedef float e_loc;


struct coords {
 e_loc x,y,z,rx,ry,rz;
};

struct frustumSizes {
 e_loc x,y,znear,zfar;
};

class triangle;
typedef vector <triangle *> tris_list;


class vertex {
public:
    e_loc x, y, z,u,v;
    virtual bool operator==(vertex &v);
    vertex();
    vertex(e_loc x,e_loc y,e_loc z);
    vertex(e_loc x,e_loc y,e_loc z,e_loc u,e_loc v);
    
};
typedef vector <vertex *> vert_list;
class triangle {
protected:
	//virtual void setVerts(vertex *a,vertex *b,vertex *c);
public:
    vertex *v[3];
    virtual bool operator==(triangle &t);
    triangle();
    triangle(vertex *a,vertex *b,vertex *c);
    triangle(vertex v[3]);
};

class shape {
    /*unsigned int n_tris;
    triangle * tris;
     * */
	e_loc scale;
    vector <vertex *> vertices;
    vector <triangle *> triangles;
public:
    bool operator==(shape &s);
    virtual vector <triangle *> getTris();
    virtual vert_list getVertices();
    virtual void addVertices(vertex *vs,int num_tris);
    void setScale(e_loc scale);
	virtual e_loc getScale();
    /*
     Dodaje trójkąt do bryły przyporządkowując wieszchołki wspólne
     */
    virtual triangle * addTriangle(triangle *t);
    virtual triangle * addTriangle(vertex v[3]);
    /*
     Dodaje wierchołek, jeśli nie istnieje i zwraca wskaźnik do niego. Jeśli już istnieje zwraca wskaźnik
     */
    virtual vertex * addVertex(vertex *v);
    virtual vertex * addVertex(e_loc x,e_loc y,e_loc z);
    /*
     Szuka identycznego wieszchołka i zwraca go
     */
    virtual vertex * findVertex(vertex *v);
     ~shape();
};


#endif	/* TYPES_HPP */

