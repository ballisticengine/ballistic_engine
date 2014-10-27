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

/*welokąty*/

poly::poly() {
}

poly::poly(vert_list vs) {
 this->v=vs;
}

bool poly::operator==(poly &p) {
	for (int i = 0; i < v.size(); i++) {
        if (!(p.v[i] == this->v[i])) {
            return false;
        }
    }
    return true;
}

void poly::calculateNormals() {
	
	MathTypes::vector v1=v[0]->diff(*v[1]),v2=v[1]->diff(*v[2]);
	v1.normalize();
	v2.normalize();
	MathTypes::vector cp=v1.crossProduct(&v2);
	for(int i=0; i<v.size(); i++) {
		
		v[i]->normal=cp;
		//v[i]->normal=v[i]->unit().vproduct(&v[i-1]->unit());
		//verts[i]->normal.write();
	}
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
		this->v[i]=&v[i];
    }
}

bool triangle::operator==(triangle &p) {
	for (int i = 0; i < 3; i++) {
        if (!(p.v[i] == this->v[i])) {
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
    for (int i=0; i < triangles.size(); i++) {
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
	return t;
}

triangle * shape::addTriangle(vertex v[3]) {
    triangle *t = new triangle(v);
    return this->addTriangle(t);

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
   return  this->addVertex(v);
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

void shape::setScale(e_loc scale) {
	this->scale=scale;
}

e_loc shape::getScale() {
 return scale;
}

vector <poly *> shape::getPolys() {
	return this->polys;
}

void shape::addPoly(poly *p) {
	this->polys.push_back(p);
	for (int i=0; i<p->v.size(); i++) {
		this->addVertex(p->v[i]);
	}
}

void shape::calculateNormals() {
	vert_list verts=this->getVertices();
	cout << "VSX: " << verts.size() << endl;
	for(int i=1; i<verts.size(); i++) {
		//verts[i]->normal=vertices[i]->unit().vproduct(&vertices[i-1]->unit());
		//verts[i]->normal.write();
	}
}