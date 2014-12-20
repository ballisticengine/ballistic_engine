#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "ObjectEntity.hpp"
#include <cmath>

using namespace std;

typedef vector <entity *> ent_list;
typedef vector <ObjectEntity *> obj_list;

typedef vector <light *> lights_list;
typedef vector <PhysicalEntity *> phys_list;

class roomEntity : public ObjectEntity {
protected:
	
public:
	ent_list entities;
	phys_list phys_entities;
	obj_list models;
	lights_list lights;
	bounding_list boundings;
	colorRGBA ambient_light;
	void addEntity(entity *e);
	void addPhysicalEntity(PhysicalEntity *e);
	void addObjectEntity(ObjectEntity *e);
	void addLightEntity(light *e);
	roomEntity();
	virtual MathTypes::vector collides(BoundingCube *bound,coords offset);
};

#endif