/**
* Zestaw klas definujący podstawowe typy używane przez silnik, nie uwzględnia struktur matematycznych (wektory,macierze), które
* obsugiwane są w klasach zawartych w mathTypes.hpp
*/

#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>

#include "mathTypes.hpp"

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
 e_loc x,y,z,rx,ry,rz;
};

struct frustumSizes {
 e_loc x,y,znear,zfar;
};

//class triangle;




class vertex : public MathTypes::vector {
public:
    e_loc u,v;
     MathTypes::vector normal ;
	virtual bool operator==(vertex &v);
    vertex();
    vertex(e_loc x,e_loc y,e_loc z);
    vertex(e_loc x,e_loc y,e_loc z,e_loc u,e_loc v);
};

typedef vector <vertex *> vert_list;

class poly {
public:
	vert_list v;
	virtual bool operator==(poly &p);
	poly();
	poly(vert_list vs);
	virtual void calculateNormals();
};

typedef vector <poly *> poly_list;

class triangle : public poly {
public:
	triangle();
	triangle(vertex *a,vertex *b,vertex *c);
    triangle(vertex vs[3]);

};


typedef vector <triangle *> tris_list;

typedef vector <poly *> poly_list;
class shape {
	e_loc scale;
    vector <vertex *> vertices;
    vector <triangle *> triangles;
	vector <poly *> polys;
public:
    bool operator==(shape &s);
    virtual vector <triangle *> getTris();
    virtual vert_list getVertices();
	virtual vector <poly *> getPolys();
	virtual void calculateNormals();
	virtual void addPoly(poly *p);
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

