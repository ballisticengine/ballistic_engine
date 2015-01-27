#include "types/shape.hpp"

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
    
    MathTypes::vector vec1,vec2,vec3,v1,v2,v3,d1,d2,d3;
    MathTypes::BasicVector n1,n2,n3;
    for(int i=0; i<this->f_count; i++) {
        for(int n=0; n<3; n++) {
        this->faces[i].normals=new MathTypes::BasicVector[3];
        v1=this->vertices[this->faces[i].index[0]];
        v2=this->vertices[this->faces[i].index[1]];
        v3=this->vertices[this->faces[i].index[2]];
        d1=v1-v2;
        d2=v3-v2;
        d3=v1-v3;
        n1=d1.crossProduct(&d2).getBasicVector();
        n2=d3.crossProduct(&d2).getBasicVector();
        n3=d3.crossProduct(&d1).getBasicVector();
        this->faces[i].normals[0]=n1;
        this->faces[i].normals[1]=n2;
        this->faces[i].normals[2]=n3;
        }
    }
}

