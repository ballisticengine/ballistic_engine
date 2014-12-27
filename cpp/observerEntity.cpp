#include "observerEntity.hpp"

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

camera * ObserverEntity::getCamera() {
 
 cam->locate(x,y+headbob_add,z);
 cam->face(rx,ry,rz);
 
 return this->cam;
}



ObserverEntity::ObserverEntity() {
	this->bounding_box=new BoundingCube(1,1,1);
	headbob_i=0;
	bob_timer.getDiffR();
}

ObserverEntity::~ObserverEntity() {
	//delete this->cam;
}