#ifndef OBSERVER_ENTITY_H
#define OBSERVER_ENTITY_H

#include "types/types.hpp"
#include "types/mathTypes.hpp"
#include "entities/physicalEntity.hpp"
#include "entities/camera.hpp"
#include "time/timer.hpp"

class ObserverEntity : public PhysicalEntity {
protected:
	camera *cam;
	e_loc headbob_add,headbob_i;
	Timer bob_timer;

public:
	ObserverEntity();
	virtual ~ObserverEntity();
	virtual void setCamera(camera *c);
	virtual camera *getCamera();
	virtual void bobHead();
	
	virtual void translate(e_loc x,e_loc y,e_loc z);	
	virtual void rotate(e_loc x,e_loc y, e_loc z);
	virtual void locate(e_loc x,e_loc y,e_loc z);
	virtual void face(e_loc x,e_loc y,e_loc z);
	


};

#endif