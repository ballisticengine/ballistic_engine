#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include "types/types.hpp"
#include "types/mathTypes.hpp"
#include "entities/entity.hpp"
#include "time/timer.hpp"


class PhysicalEntity : public Entity {
protected:
	
	void setIfNotZero(e_loc &a,e_loc &b);
public:
	Coords velocity,acceleration;
        e_loc weight;
	PhysicalEntity();
	Coords nextCoords(time_int diff);
	void changeVelocity(Coords velocity);
	void setVelocity(Coords velocity);
        bool no_physics;
	//void resetT();
	Coords getVelocity();
	void printVelocity();
	

};

#endif