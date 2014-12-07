#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "ObjectEntity.hpp"
#include <cmath>

using namespace std;

class roomEntity : public ObjectEntity {
protected:
	shape *bounding;
public:
	roomEntity();
	
	virtual shape *getBoundingShape();
};

#endif