
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
    vector <vertex> vertices;
    vector <triangle *> triangles;
public:
    bool operator==(shape &s);
    
    /*
     Dodaje trójkąt do bryły przyporządkowując wieszchołki wspólne
     */
    triangle * addTriangle(triangle *t);
    /*
     Dodaje wierchołek, jeśli nie istnieje i zwraca wskaźnik do niego. Jeśli już istnieje zwraca wskaźnik
     */
    vertex * addVertex(vertex *v);
    vertex * addVertex(e_loc x,e_loc y,e_loc z);
    /*
     Szuka identycznego wieszchołka i zwraca go
     */
    vertex * findVertex(vertex *v);
};


#endif	/* TYPES_HPP */

