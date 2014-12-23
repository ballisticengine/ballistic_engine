#include "types.hpp"


shape::~shape() {

}
void shape::setVertices(v_type *vs,size_t count) {
	this->vertices=vs;
	this->v_count=count;
}

void shape::setNormals(n_type *normals) {
	this->normals=normals;
	
}


void shape::setUvs(uv *uvs,size_t count) {

}

void shape::setScale(e_loc scale) {
	this->scale=scale;
}

e_loc shape::getScale() {
 return scale;
}


void shape::calculateNormals() {
	/*vert_list verts=this->getVertices();
	poly_list pl=getPolys();
	for(int i=0; i<pl.size(); i++) {
		pl[i]->calculateNormals();
	}

	for(int i=0; i<verts.size(); i++) {
		if(!verts[i]->has_normal)
			cout << "No normal for << " << i << "\n";
	}*/
}

void shape::setRendererHint(void *hint) {
	this->renderer_hint=hint;
}

void * shape::getRendererHint() {
	return this->renderer_hint;
}

