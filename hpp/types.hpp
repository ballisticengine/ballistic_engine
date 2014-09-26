/**
* Zestaw klas definujący podstawowe typy używane przez silnik, nie uwzględnia struktur matematycznych (wektory,macierze), które
* obsugiwane są w klasach zawartych w mathTypes.hpp
*/

#ifndef TYPES_HPP
#define	TYPES_HPP

#include <vector>
#include <iostream>


using namespace std;

typedef double e_loc;

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

class poly {
public:
	vert_list v;
	virtual bool operator==(poly &p);
	poly();
	poly(vert_list vs);
};

typedef vector <poly *> poly_list;

//TODO: dziedziczyć po poly
class triangle {
protected:
	//virtual void setVerts(vertex *a,vertex *b,vertex *c);
public:
    vertex *v[3];
	triangle();
    triangle(vertex *a,vertex *b,vertex *c);
    triangle(vertex v[3]);
	bool triangle::operator==(triangle &t);
};



class shape {
    /*unsigned int n_tris;
    triangle * tris;
     * */
	e_loc scale;
    vector <vertex *> vertices;
    vector <triangle *> triangles;
	vector <poly *> polys;
public:
    bool operator==(shape &s);
    virtual vector <triangle *> getTris();
    virtual vert_list getVertices();
	virtual vector <poly *> getPolys();
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

