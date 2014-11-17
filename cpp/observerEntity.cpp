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

	
}