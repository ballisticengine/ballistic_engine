

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
#include "factories/shapeFactory.hpp"
#include "factories/textureFactory.hpp"
#include "config/EngineState.hpp"
#include "types/mathTypes.hpp"
#include "entities/light.hpp"
#include "entities/pointlight.hpp"
#include "dontcare/terrainMap.hpp"
#include "time/timer.hpp"
#include "entities/observerEntity.hpp"
#include "types/material.hpp"
#include "entities/sprite.hpp"
#include "misc/utils.hpp"
#include "python/scripting.hpp"
#include "python/locker.hpp"
#include "world/PreloadStore.hpp"
#include "world/Octree.hpp"
#include "physics/collisionDetector.hpp"
#include "misc/xmlHelper.hpp"




struct PyEntityCollisionParams {
    ObjectEntity *a, *b;
};

class World {
protected:
    Camera default_Camera;
    void moveEntity(ObjectEntity *e, time_int time_diff, bool skip_collision);
    void moveEntities();
    Timer time;
    TerrainMap *tm;
    PyLocker *locker;
    bool moving_lock;
    queue<ObjectEntity *> spawn_queue;
    OctreeNode *octree;
    CollisionDetector collisions;
    void cleanup();

public:
    ObserverEntity observer;
    RoomEntity *active_room;
    Sprite *testsprite;
    Skybox *sky;
    rooms_list rooms;
    e_loc roomrot_x, roomrot_y, roomrot_z;

    static World *getInstance();
    static World & getRef();




    World();
    ~World();

    //obj_reflist getModelsRef();

    Camera *getCurrentCamera();
    bool parseXml(string &fn);
    bool saveXml(string fn);
    void prepare();
    void operator()();
    RoomEntity * getActiveRoom();
    ObserverEntity * getObserver();
    TerrainMap * getTerrain();


    void addRoomEntity(RoomEntity *e);

};

#endif	/* WORLD_HPP */

