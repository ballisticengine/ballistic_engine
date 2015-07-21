#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "entities/ObjectEntity.hpp"
#include "types/boundingCube.hpp"
#include "types/plane.hpp"
#include "anim/modelAnimator.hpp"
#include "misc/utils.hpp"
#include "entities/light.hpp"
#include "entities/sprite.hpp"
#include "world/PreloadStore.hpp"
#include "types/shape.hpp"
#include <cmath>

using namespace std;

typedef vector <Entity *> ent_list;
typedef vector <ObjectEntity *> obj_list;
typedef vector <Light *> lights_list;
typedef vector <Sprite *> sprite_list;
typedef vector <Sprite *> decal_list;

class RoomEntity : public ObjectEntity {
protected:
    PreloadStore *preload_store;
public:
	//ModelAnimator model_animator;
	ent_list entities;
	obj_list models;
	lights_list lights;
	bounding_list boundings;
        decal_list decals;
	ColorRGBA ambient_light;
	void addEntity(Entity *e);
	void addObjectEntity(ObjectEntity *e);
	void addLightEntity(Light *e);
	void placeDecal(Sprite *decal,Coords c);
        void placePreloadDecal(string preload,Coords c);
        void placeDecalTexture(Texture *tex,Coords c);
        void removeObjectEntity(string name);
        ObjectEntity * spawnObject(string preload_name,Coords c,string object_name="");
        ObjectEntity * spawnShape(Shape *s,Coords c,string object_name="");
        RoomEntity();
	~RoomEntity();
//	virtual CollisionInfo collides(ObjectEntity *ent,Coords offset);
        virtual void calcBoundings();
};

typedef vector <RoomEntity *> rooms_list;

#endif