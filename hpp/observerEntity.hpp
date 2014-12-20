#ifndef OBSERVER_ENTITY_H
#define OBSERVER_ENTITY_H

#include "types.hpp"
#include "mathTypes.hpp"
#include "physicalEntity.hpp"
#include "camera.hpp"
#include "timer.hpp"

class ObserverEntity : public PhysicalEntity {
protected:
	camera *cam;
	e_loc headbob_add,headbob_i;
	Timer bob_timer;

public:
	ObserverEntity();
	virtual void setCamera(camera *c);
	virtual camera *getCamera();
	virtual void bobHead();
	


};

#endif