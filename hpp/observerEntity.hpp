#ifndef OBSERVER_ENTITY_H
#define OBSERVER_ENTITY_H

#include "types.hpp"
#include "mathTypes.hpp"
#include "physicalEntity.hpp"
#include "camera.hpp"

class ObserverEntity : public PhysicalEntity {
protected:
	camera *cam;
	shape *bounding;
public:
	ObserverEntity();
	virtual void setCamera(camera *c);
	virtual camera *getCamera();
	virtual shape *getBoundingShape();


};

#endif