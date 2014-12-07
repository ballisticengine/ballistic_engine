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

bool entity::collides(entity *e)//,coords offset) 

{
	
	
	BoundingCube *a=this->getBoundingBox(),*b=e->getBoundingBox();
	coords ac=this->getCoords(),bc=e->getCoords();

	MathTypes::vector amax,amin,bmax,bmin;
	
	

	amax=a->max;//+ac.translation;
	amin=a->min;//+ac.translation;
	bmax=b->max;//+bc.translation;
	bmin=b->min;//+bc.translation;
	
	b->max.write();
	//cout << bc.translation.x << ", " << bc.translation.y << ", " << bc.translation.z << endl;

	bool collide=(
		amax.x > bmin.x && 
		 amin.x < bmax.x &&
		amax.y > bmin.y &&
		 amin.y < bmax.y &&
		 amax.z > bmin.z &&
		amin.z < bmax.z
		);



	return collide;
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
