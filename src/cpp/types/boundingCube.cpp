#include "types/boundingCube.hpp"

BoundingCube::BoundingCube() {
	
}

BoundingCube::BoundingCube(Shape *s) {
	this->calculate(s);
	calculateSizes();
}



e_loc BoundingCube::toSphereRadius() {
	Vector3d E=(max-min)/2.0f;	
	Vector3d center=min+E;
	
	return 0;
}

void BoundingCube::rotate(e_loc x,e_loc y,e_loc z) {
//    e_loc tmp;
//    if(x) {
//        tmp=max.z;
//        max.z=max.y;
//        max.y=tmp;
//        tmp=min.z;
//        min.z=min.y;
//        min.y=tmp;
//    }
}

BoundingCube::BoundingCube(e_loc width,e_loc height,e_loc depth) {
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

BoundingCube::BoundingCube(e_loc minx,e_loc miny,e_loc minz,e_loc maxx,e_loc maxy,e_loc maxz) {
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
	//e_loc max_x,min_x,max_y,min_y,max_z,min_z;
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
	e_loc tmp1,tmp2;
        tmp1=min.z;
        tmp2=max.z;
        min.z=min.y;
        max.z=max.y;
        min.y=tmp1;
        max.y=tmp2;
        
}

e_loc BoundingCube::getWidth() {
	return this->width;
}

e_loc BoundingCube::getHeight() {
	return this->height;
}

e_loc BoundingCube::getDepth() {
	return this->depth;
}

void BoundingCube::print() {
// cout << "Max x " << max_x << "|" << "Min y " << min_y << 
}