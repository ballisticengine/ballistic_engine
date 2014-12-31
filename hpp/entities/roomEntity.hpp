#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "entities/ObjectEntity.hpp"
#include "types/boundingCube.hpp"
#include "anim/modelAnimator.hpp"
#include "misc/utils.hpp"
#include <cmath>

using namespace std;

typedef vector <entity *> ent_list;
typedef vector <ObjectEntity *> obj_list;

typedef vector <light *> lights_list;
typedef vector <PhysicalEntity *> phys_list;

class roomEntity : public ObjectEntity {
   
public:
	ModelAnimator model_animator;
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
	~roomEntity();
	virtual MathTypes::vector collides(entity *ent,coords offset);
};

#endif