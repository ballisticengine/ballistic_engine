#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "objectEntity.hpp"

class roomEntity : public objectEntity {
protected:
	shape *bounding;
public:
	roomEntity();
	virtual shape *getBoundingShape();
};

#endif