#include "types.hpp"

/* operacje na wieszchołkach */

bool vertex::operator==(vertex &v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    return false;
}

vertex::vertex() {
    x = 0;
    y = 0;
    z = 0;
}

vertex::vertex(e_loc x, e_loc y, e_loc z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vertex::vertex(e_loc x, e_loc y, e_loc z, e_loc u, e_loc v) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->u = u;
    this->v = v;
}

/* trójkąty */

triangle::triangle() {

}

triangle::triangle(vertex *a, vertex *b, vertex *c) {
    this->v[0] = a;
    this->v[1] = b;
    this->v[2] = c;
}

triangle::triangle(vertex v[3]) {
    for (int i = 0; i < 3; i++) {
        this->v[i] = &v[i];
    }
}

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

triangle * shape::addTriangle(triangle *t) {
    for (int i = 0; i < 3; i++) {
        this->addVertex(t->v[i]);
        triangles.push_back(t);
    }
}

triangle * shape::addTriangle(vertex v[3]) {
    triangle *t = new triangle(v);
    this->addTriangle(t);

}

vertex * shape::addVertex(vertex *v) {
    if (vertices.size() != 0) { //
        vertex *f = findVertex(v);
        if (f) {
            return f;
        } else {
            vertices.push_back(v);
            return v;
        }
    } else {
        vertices.push_back(v);
        return v;
    }
}

vertex * shape::addVertex(e_loc x, e_loc y, e_loc z) {
    vertex *v = new vertex(x, y, z);
    this->addVertex(v);
}

vertex * shape::findVertex(vertex *v) {
    for (int i = 0; i < vertices.size(); i++) {
        if (*vertices[i] == *v) {
            return vertices[i];
        }
    }
    return 0;
}

void shape::addVertices(vertex *vs, int num_tris) {
    for (int i = 0; i < num_tris; i++) {
        vertices.push_back(&vs[i]);
    }
}

vert_list shape::getVertices() {
    return vertices;
}

vector <triangle *> shape::getTris() {
    //    cout << vertices.size() << endl;
    return this->triangles;
}

shape::~shape() {

}