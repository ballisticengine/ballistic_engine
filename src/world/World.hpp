

#ifndef WORLD_HPP
#define	WORLD_HPP


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <queue>
#include <boost/algorithm/string.hpp>    

using namespace std;
using namespace boost::property_tree;
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "entities/RoomEntity.hpp"
#include "entities/Camera.hpp"
#include "misc/singleton.hpp"
#include "types/skybox.hpp"
#include "config/Config.hpp"
#include "resources/ResourceManager.hpp"
#include "config/EngineState.hpp"
#include "types/Vector3d.hpp"
#include "entities/light.hpp"
#include "entities/pointlight.hpp"
#include "time/timer.hpp"
#include "entities/observerEntity.hpp"
#include "types/material.hpp"
#include "entities/sprite.hpp"
#include "misc/utils.hpp"
#include "python/scripting.hpp"
#include "python/locker.hpp"
#include "world/PreloadStore.hpp"
#include "world/Octree.hpp"
#include "physics/BulletPhysics.hpp"
#include "misc/xmlHelper.hpp"
#include "libload/LibLoad.hpp"

struct PyEntityCollisionParams {
    ObjectEntity *a, *b;
};

class World {
protected:

    void moveEntity(ObjectEntity *e, time_int time_diff, bool skip_collision);
    void moveEntities();
    Timer time;

    PyLocker *locker;
    bool moving_lock;
    queue<ObjectEntity *> spawn_queue;
    OctreeNode *octree;
    BulletPhysics collisions;
    void cleanup();
    size_t entity_counter;
public:
    BulletPhysics *getPhysics();
    Camera default_Camera;
    ObserverEntity observer;
    RoomEntity *active_room;
    Sprite *testsprite;
    Skybox *sky;
    rooms_list rooms;
    scalar_t roomrot_x, roomrot_y, roomrot_z;

    BulletPhysics getPhysicsEngine();


    World();
    ~World();

    //obj_reflist getModelsRef();

    Camera *getCurrentCamera();
    void prepare();
    void operator()();
    RoomEntity * getActiveRoom();
    ObserverEntity * getObserver();



    void addRoomEntity(RoomEntity *e);
    void colorize();
    ObjectEntity *findEntityByColor(ColorRGBA c);
    ObjectEntity *findEntityByID(size_t id);

};

#endif	/* WORLD_HPP */

