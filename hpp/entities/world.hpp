

#ifndef WORLD_HPP
#define	WORLD_HPP


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;
using namespace boost::property_tree;
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "entities/roomEntity.hpp"
#include "entities/camera.hpp"
#include "misc/singleton.hpp"
#include "types/skybox.hpp"
#include "config/config.hpp"
#include "factories/shapeFactory.hpp"
#include "factories/textureFactory.hpp"
#include "config/engineState.hpp"
#include "types/mathTypes.hpp"
#include "entities/light.hpp"
#include "entities/pointlight.hpp"
#include "dontcare/terrainMap.hpp"
#include "time/timer.hpp"
#include "entities/observerEntity.hpp"
#include "types/material.hpp"
#include "entities/sprite.hpp"
#include "misc/utils.hpp"
//#include "python.hpp"

typedef vector <roomEntity *> rooms_list;

struct PyEntityCollisionParams {
	PhysicalEntity *a,*b;
};

class world {
protected:
	
	
	camera default_camera;
	void moveEntity(PhysicalEntity *e,time_int time_diff,bool skip_collision);
	void moveEntities();
	Timer time;
	TerrainMap *tm;
	
public:
	ObserverEntity observer;
	roomEntity *active_room;
	Sprite *testsprite;
	skybox *sky;
	rooms_list rooms;

	static world *getInstance(); 
	static world & getRef();
	
	world();
	~world();
	
	//obj_reflist getModelsRef();

	camera *getCurrentCamera();
	bool parseXml(string &fn);
	void prepare();
	void operator()();
	roomEntity * getActiveRoom();
	ObserverEntity * getObserver();
	TerrainMap * getTerrain();

	
	void addRoomEntity(roomEntity *e);

};

#endif	/* WORLD_HPP */

