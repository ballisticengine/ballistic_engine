#include "types.hpp"

uv::uv(e_loc u,e_loc v) {
	this->u=u;
	this->v=v;
}

uv::uv() {
	u=0;
	v=0;
}

/* operacje na wieszchołkach */

bool vertex::operator==(vertex &v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    return false;
}

vertex::vertex() {
    has_normal=false;
	x = 0;
    y = 0;
    z = 0;
}

vertex::vertex(e_loc x, e_loc y, e_loc z) {
    has_normal=false;
	this->x = x;
    this->y = y;
    this->z = z;
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
	MathTypes::vector va,vb,cp;
	va=v[0]->diff(*v[2]);
	vb=v[1]->diff(*v[2]);
		cp=va.crossProduct(&vb);
		cp=cp.normalize();
		v[0]->normal=cp;
		v[0]->has_normal=true;
	
	for(int i=0; i<v.size(); i++) {
		v[i]->normal=cp;
		v[i]->has_normal=true;
	}

	/*for(int i=2; i<v.size(); i++) {
		va=v[i-2]->diff(*v[i]);
		vb=v[i-1]->diff(*v[i]);
		cp=va.crossProduct(&vb);
		v[i]->normal=cp;
		v[i]->has_normal=true;
	}*/
	return;
	/*
	static int cnt=0;

	MathTypes::vector va,vb,cp;//-v[0];

	
	va=v[0]->diff(*v[2]);
	vb=v[1]->diff(*v[2]);
		cp=va.crossProduct(&vb);


	
	
	cp=cp.normalize();
	v[0]->normal=cp;
	v[1]->normal=cp;
	v[2]->normal=cp;
	v[0]->has_normal=true;
	v[1]->has_normal=true;
	v[2]->has_normal=true;
	//cout << "tVS: " << v.size() << ", " << cnt << endl;
	cnt++;
	return;
	*/
}


	




/* nowe trójkąty */

triangle::triangle() {
}

triangle::triangle(vertex *a,vertex *b,vertex *c) {
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
}


triangle::triangle(vertex vs[3]) {
	v.push_back(&vs[0]);
	v.push_back(&vs[1]);
	v.push_back(&vs[2]);
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

vertex * shape::addVertex(vertex *v,uv *uvs) {
	
	this->uvs.push_back(uvs);
	return this->addVertex(v);
}

vertex * shape::addVertex(vertex *v) {
    if (vertices.size() != 0) { 
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
    //return 0;
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

uv_list shape::getUvs() {
 return uvs;
}

vector <poly *> shape::getPolys() {
	return this->polys;
}

void shape::addPoly(poly *p) {
	this->polys.push_back(p);
	for (int i=0; i<p->v.size(); i++) {
		p->v[i]=this->addVertex(p->v[i]);
	}
}

void shape::calculateNormals() {
	vert_list verts=this->getVertices();
	poly_list pl=getPolys();
	for(int i=0; i<pl.size(); i++) {
		pl[i]->calculateNormals();
	}

	for(int i=0; i<verts.size(); i++) {
		if(!verts[i]->has_normal)
			cout << "No normal for << " << i << "\n";
	}
}

void shape::setRendererHint(void *hint) {
	this->renderer_hint=hint;
}

void * shape::getRendererHint() {
	return this->renderer_hint;
}

 int shape::getPolyCount() {
	poly_list p=getPolys();
	int count=p[0]->v.size();
	return count;
 }