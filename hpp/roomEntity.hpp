#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "ObjectEntity.hpp"
#include <cmath>

using namespace std;

class roomEntity : public ObjectEntity {
protected:
	
public:
	bounding_list boundings;
	roomEntity();
	virtual MathTypes::vector collides(BoundingCube *bound,coords offset);
};

#endif