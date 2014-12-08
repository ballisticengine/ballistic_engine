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
	 this->bounding_box->loc.x=this->x;
	 this->bounding_box->loc.y=this->y;
	 this->bounding_box->loc.z=this->z;
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

MathTypes::vector entity::collides(BoundingCube *bound,coords offset) 

{
	
	return collisionTest(this->bounding_box,bound,offset);
	
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

bool hitTest(BoundingCube *a,BoundingCube *b,MathTypes::vector offset) {
	MathTypes::vector amax,amin,bmax,bmin;
	amax=a->max-offset;
	amin=a->min-offset;
	bmax=b->max-offset;
	bmin=b->min-offset;
	
	//offset.write();

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

MathTypes::vector collisionTest(BoundingCube *a,BoundingCube *b,coords offset) {

	
	
	MathTypes::vector res,offsetx=offset.translation,offsety=offset.translation,offsetz=offset.translation;
	
	offsetx.y=offsetx.z=0;
	offsety.x=offsety.z=0;
	offsetz.x=offsetz.y=0;



	res.x=res.y=res.z=0;

	if(hitTest(a,b,offsetx)) {
	 res.x=1;
	}

	if(hitTest(a,b,offsety)) {
	 res.y=1;
	}

	if(hitTest(a,b,offsetz)) {
	 res.z=1;
	}
	return res;
}