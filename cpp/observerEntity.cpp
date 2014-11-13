#include "observerEntity.hpp"

void ObserverEntity::setCamera(camera *c) {
	this->cam=c;
}

camera * ObserverEntity::getCamera() {
 cam->locate(x,y,z);
 cam->face(rx,ry,rz);
	return this->cam;
}

shape *ObserverEntity::getBoundingShape() {
	return this->bounding;
}

ObserverEntity::ObserverEntity() {

	shape * bounding=new shape();
	bounding->addVertex(new vertex(0,0,0));
}