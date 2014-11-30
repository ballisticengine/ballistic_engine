#include "observerEntity.hpp"

void ObserverEntity::setCamera(camera *c) {
	this->cam=c;
	
}

camera * ObserverEntity::getCamera() {
 cam->locate(x,y,z);
 cam->face(rx,ry,rz);
	return this->cam;
}



ObserverEntity::ObserverEntity() {
	this->bounding_box=new BoundingCube(2,2,2);
}