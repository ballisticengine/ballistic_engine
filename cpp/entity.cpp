#include "entity.hpp"


coords entity::getCoords() {
	coords c;
	c.x=x;
	c.y=y;
	c.z=z;
	c.rx=rx;
	c.ry=ry;
	c.rz=rz;
	return c;
}

void entity::translate(e_loc x,e_loc y,e_loc z) {
 this->x+=x;
 this->y+=y;
 this->z+=z;
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
	this->translate(c.x,c.y,c.z);
}

entity::entity() {
 
}

/*Note offset to w³aœciwie nowa pozycja, a nie przemieszczenie */

bool entity::collides(entity *e)//,coords offset) 

{
	
	//if(!this->getBoundingBox() || e->getBoundingBox()) {
	 //cout << "nope";
	//	return false;
	//} 

	BoundingCube *a=this->getBoundingBox(),*b=e->getBoundingBox();
	coords ac=this->getCoords(),bc=e->getCoords();

	e_loc 
		  amax_x=a->max_x+ac.x,
		  amin_x=a->min_x+ac.x,
		  amax_y=a->max_y+ac.y,
		  amin_y=a->min_y+ac.y,
		  amax_z=a->max_z+ac.z,
		  amin_z=a->min_z+ac.z,
		  
		  bmax_x=-(b->min_x+bc.x),
		  bmin_x=-(b->max_x+bc.x),
		  bmax_y=b->max_y+bc.y,
		  bmin_y=b->min_y+bc.y,
		  bmax_z=-(b->min_z+bc.z),
		  bmin_z=-(b->max_z+bc.z)
		
		  ;

	
	//static unsigned int ii=0;
	//cout << amax_x << ", " << amin_x << ", " << amax_y << ", " << amin_y << ", " << amax_z << ", " << amin_z << endl;
//	cout << bmax_x << ", " << bmin_x << ", " << bmax_y << ", " << bmin_y << ", " << bmax_z << ", " << bmin_z << endl;
//	cout << "------------------" << endl;
//	if(ii==1000) {
//		while(1) {}
//	}
	//ii++;

	bool collide=(
		amax_x > bmin_x && 
		 amin_x < bmax_x &&
		amax_y > bmin_y &&
		 amin_y < bmax_y &&
		 amax_z > bmin_z &&
		amin_z < bmax_z
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
