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
    if (s.tris.size() != this->tris.size()) {
        return false;
    }
    for (int i; i < tris.size(); i++) {
        if (!(*(s.tris[i]) == *(this->tris[i]))) {
            return false;
        }
    }
    return true;
}



void shape::addVertex(vertex *v) {
    if(tris.size()>0) {
        
    } else {
       tris.push_back(v); 
    }
}

void shape::addVertex(e_loc x, e_loc y, e_loc z) {
    vertex *v = new vertex(x,y,z);
    this->addVertex(v);
}

vertex * shape::findVertex(vertex *v) {
    for(int i=0; i<tris.size(); i++) {
        if(*tris[i]==*v) {
            return tris[i];
        }
    }
    return 0;
}