#include "entity.hpp"


coords entity::getCoords() {
	coords c;
	c.translation.x=x;
	c.translation.y=y;
	c.translation.z=z;
	c.rotation.x=rx;
	c.rotation.y=ry;
	c.rotation.z=rz;
	return c;
}

void entity::translate(e_loc x,e_loc y,e_loc z) {
 this->x+=x;
 this->y+=y;
 this->z+=z;
 if(this->bounding_box) {
	 this->bounding_box->max.x+=x;
	 this->bounding_box->max.y+=y;
	 this->bounding_box->max.z+=z;
	 this->bounding_box->min.x+=x;
	 this->bounding_box->min.y+=y;
	 this->bounding_box->min.z+=z;
 }
}

void entity::rotate(e_loc x,e_loc y, e_loc z) {
 this->rx+=x;
 this->ry+=y;
 this->rz+=z;
}

void entity::locate(e_loc x,e_loc y,e_loc z) {
 this->x=x;
 this->y=y;
 this->z=z;
}

void entity::face(e_loc x,e_loc y,e_loc z) {
 this->rx=x;
 this->ry=y;
 this->rz=z;
}

void entity::translate(coords c) {
	this->translate(c.translation.x,c.translation.y,c.translation.z);
}

entity::entity() {
 
}

/* offset to w³aœciwie nowa pozycja, a nie przemieszczenie */

bool entity::collides(BoundingCube *bound)//,coords offset) 

{
	
	return collisionTest(this->bounding_box,bound);
	
}

void entity::setBoundingBox(BoundingCube *box) {
	this->bounding_box=box;
}

BoundingCube * entity::getBoundingBox() {
	return this->bounding_box;
}

void entity::makeBoundingBox() {
	///
}

bool collisionTest(BoundingCube *a,BoundingCube *b,e_loc factor) {

	

	MathTypes::vector amax,amin,bmax,bmin;
	
	

	amax=a->max;//+ac.translation;
	amin=a->min;//+ac.translation;
	bmax=b->max;//+bc.translation;
	bmin=b->min;//+bc.translation;
	
	

	bool collide=(
		amax.x*factor > bmin.x*factor && 
		 amin.x*factor < bmax.x*factor &&
		amax.y*factor > bmin.y*factor &&
		 amin.y*factor < bmax.y*factor &&
		 amax.z*factor > bmin.z*factor &&
		amin.z*factor < bmax.z*factor
		);



	return collide;
}