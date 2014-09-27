#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include "types.hpp"
#include "mathTypes.hpp"
#include "entity.hpp"
#include "timer.hpp"

struct TrRot {
 MathTypes::vector t,r;
};

class PhysicalEntity : public entity {
protected:
	TrRot velocity,acceleration;
public:
	coords nextCoords(time_int diff);
	void setVelocity(TrRot velocity);
	TrRot getVelocity();
	

};

#endif