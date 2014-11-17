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

bool entity::collides(entity *e,coords offset) {
	//cout << "C";
	//cout << this->getBoundingShape() ;
	if(!this->getBoundingShape()) {
	 return false;
	} 
	shape *target_bs=e->getBoundingShape();
	poly_list target_ps=target_bs->getPolys(),
		src_ps=this->getBoundingShape()->getPolys();
	for(int i=0; i<src_ps.size(); i++) {
		
		for(int n=0; n<target_ps.size(); n++) {
			
		}
	}
}

shape * entity::getBoundingShape() {
 return NULL;
}