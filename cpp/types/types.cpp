#include "types/types.hpp"

/* ShapeAbstract */


ShapeAbstract::~ShapeAbstract() {
if(this->vertices) {
		delete this->vertices;
	}

	if(this->normals) {
		delete this->normals;

	}

	if(this->faces) {
		delete this->faces;
	}

	if(this->uvs) {
		delete this->uvs;
	}
}

/* shape */

 shape::shape() {
 
	 this->renderer_hint=0;
 }

shape::~shape() {
	if(this->textures) {
		delete this->textures;
	}

	if(this->frames) {
		delete this->frames;
	}

	if(this->frame_times) {
	 delete this->frame_times;
	}

	


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


