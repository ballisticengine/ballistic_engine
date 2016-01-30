#include "types/boundingCube.hpp"

BoundingCube::BoundingCube() {
	
}

BoundingCube::BoundingCube(Shape *s) {
	this->calculate(s);
	calculateSizes();
}



scalar_t BoundingCube::toSphereRadius() {
	Vector3d E=(max-min)/2.0f;	
	Vector3d center=min+E;
	
	return 0;
}

void BoundingCube::rotate(scalar_t x,scalar_t y,scalar_t z) {
//    scalar_t tmp;
//    if(x) {
//        tmp=max.z;
//        max.z=max.y;
//        max.y=tmp;
//        tmp=min.z;
//        min.z=min.y;
//        min.y=tmp;
//    }
}

BoundingCube::BoundingCube(scalar_t width,scalar_t height,scalar_t depth) {
	this->width=width;
	this->height=height;
	this->depth=depth;
	max.x=width/2;
	min.x=-width/2;
	max.y=height/2;
	min.y=-height/2;
	max.z=depth/2;
	min.z=-depth/2;
}

BoundingCube::BoundingCube(scalar_t minx,scalar_t miny,scalar_t minz,scalar_t maxx,scalar_t maxy,scalar_t maxz) {
 min.x=minx;
 min.y=miny;
 min.z=minz;
 max.x=maxx;
 max.y=maxy;
 max.z=maxz;
 calculateSizes();
}

void BoundingCube::calculateSizes() {
	this->width=max.x-min.x;
	this->height=max.y-min.y;
	this->depth=max.z-min.z;
}

void BoundingCube::calculate(Shape * s) {
    cout << "BCC";
    //vert_list vs=s->getVertices();
	//scalar_t max_x,min_x,max_y,min_y,max_z,min_z;
	max.x=min.x=max.y=min.y=max.z=min.z=0;
	
	for (unsigned int i=0; i<s->v_count; i++) {
		if (s->vertices[i].x > max.x) {
			max.x=s->vertices[i].x;
		}

		if(s->vertices[i].x < min.x) {
		 min.x=s->vertices[i].x;
		}

		if (s->vertices[i].y > max.y) {
			max.y=s->vertices[i].y;
		}

		if(s->vertices[i].y < min.y) {
		 min.y=s->vertices[i].y;
		}

		if (s->vertices[i].z > max.z) {
			max.z=s->vertices[i].z;
		}

		if(s->vertices[i].z < min.z) {
		 min.z=s->vertices[i].z;
		}
	}
//
	scalar_t tmp1,tmp2;
        tmp1=min.z;
        tmp2=max.z;
        min.z=min.y;
        max.z=max.y;
        min.y=tmp1;
        max.y=tmp2;
        
}

scalar_t BoundingCube::getWidth() {
	return this->width;
}

scalar_t BoundingCube::getHeight() {
	return this->height;
}

scalar_t BoundingCube::getDepth() {
	return this->depth;
}

void BoundingCube::print() {
// cout << "Max x " << max_x << "|" << "Min y " << min_y << 
}