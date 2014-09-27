#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include "types.hpp"
#include "mathTypes.hpp"
#include "entity.hpp"
#include "timer.hpp"

class TrRot {
public:
	MathTypes::vector t,r;
	void reset();
	TrRot();
};

class PhysicalEntity : public entity {
protected:
	TrRot velocity,acceleration;
	void setIfNotZero(e_loc &a,e_loc &b);
public:
	coords nextCoords(time_int diff);
	void changeVelocity(TrRot velocity);
	void setVelocity(TrRot velocity);
	//void resetT();
	TrRot getVelocity();
	

};

#endif