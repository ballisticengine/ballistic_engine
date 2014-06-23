#include "types.hpp"

/* operacje na wieszchołkach */

bool vertex::operator==(vertex &v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    return false;
}

vertex::vertex() {
    x=0;
    y=0;
    z=0;
}

vertex::vertex(e_loc x, e_loc y, e_loc z) {
    this->x=x;
    this->y=y;
    this->z=z;
}

/* trójkąty */

bool triangle::operator==(triangle &t) {
    for (int i = 0; i < 3; i++) {
        if (!(t.v[i] == this->v[i])) {
            return false;
        }
    }
    return true;
}

/* kształty */

bool shape::operator==(shape &s) {
    if (s.triangles.size() != this->triangles.size()) {
        return false;
    }
    for (int i; i < triangles.size(); i++) {
        if (!(*(s.triangles[i]) == *(this->triangles[i]))) {
            return false;
        }
    }
    return true;
}



vertex * shape::addVertex(vertex *v) {
    if(vertices.size()>0) {
        
    } else {
       vertices.push_back(v); 
    }
}

vertex * shape::addVertex(e_loc x, e_loc y, e_loc z) {
    vertex *v = new vertex(x,y,z);
    this->addVertex(v);
}

vertex * shape::findVertex(vertex *v) {
    for(int i=0; i<vertices.size(); i++) {
        if(*vertices[i]==*v) {
            return vertices[i];
        }
    }
    return 0;
}