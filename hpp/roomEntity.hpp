#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "ObjectEntity.hpp"

class roomEntity : public ObjectEntity {
protected:
	shape *bounding;
public:
	roomEntity();
	virtual bool collides(entity *e,coords offset);
	virtual shape *getBoundingShape();
};

#endif