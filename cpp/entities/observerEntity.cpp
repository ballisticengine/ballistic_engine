#include "entities/observerEntity.hpp"

void ObserverEntity::setCamera(camera *c) {
	this->cam=c;
	
}

void ObserverEntity::bobHead() {
	//if(bob_timer.getDiffR()==0.0) {
	// cout <<bob_timer.getDiffR() << endl;
		//return;
	//}
	
 
 headbob_i+=8*bob_timer.getDiffR();
 headbob_add=sin(headbob_i)*2;
 
}

void ObserverEntity::translate(e_loc x,e_loc y,e_loc z) {
	entity::translate(x,y,z);
	this->cam->translate(x,y,z);
}

void ObserverEntity::rotate(e_loc x,e_loc y, e_loc z) {
	entity::rotate(x,y,z);
	this->cam->rotate(x,y,z);
}

void ObserverEntity::locate(e_loc x,e_loc y,e_loc z) {
	entity::locate(x,y,z);
	this->cam->locate(x,y,z);
}

void ObserverEntity::face(e_loc x,e_loc y,e_loc z) {
	entity::face(x,y,z);
	this->cam->face(x,y,z);
}

camera * ObserverEntity::getCamera() {
 
 //cam->locate(x,y+headbob_add,z);
 //cam->face(rx,ry,rz);
 
 return this->cam;
}



ObserverEntity::ObserverEntity() {
	this->bounding_box=new BoundingCube(7,7,7);
	headbob_i=0;
	bob_timer.getDiffR();
	this->cam=cam;
}

ObserverEntity::~ObserverEntity() {
	//delete this->cam;
}