#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "entities/ObjectEntity.hpp"
#include "types/boundingCube.hpp"
#include "anim/modelAnimator.hpp"
#include "misc/utils.hpp"
#include "entities/light.hpp"
#include "entities/sprite.hpp"
#include "world/PreloadStore.hpp"
#include <cmath>

using namespace std;

typedef vector <entity *> ent_list;
typedef vector <ObjectEntity *> obj_list;

typedef vector <light *> lights_list;
typedef vector <PhysicalEntity *> phys_list;
typedef vector <Sprite *> sprite_list;
typedef vector <Sprite *> decal_list;

class roomEntity : public ObjectEntity {
protected:
    PreloadStore *preload_store;
public:
	ModelAnimator model_animator;
	ent_list entities;
	phys_list phys_entities;
	obj_list models;
	lights_list lights;
	bounding_list boundings;
        decal_list decals;
	colorRGBA ambient_light;
	void addEntity(entity *e);
	void addPhysicalEntity(PhysicalEntity *e);
	void addObjectEntity(ObjectEntity *e);
	void addLightEntity(light *e);
	void placeDecal(Sprite *decal,coords c);
        void placePreloadDecal(string preload,coords c);
        ObjectEntity * spawnObject(string preload_name,coords c,string object_name="");
        roomEntity();
	~roomEntity();
	virtual MathTypes::vector collides(entity *ent,coords offset);
};

#endif