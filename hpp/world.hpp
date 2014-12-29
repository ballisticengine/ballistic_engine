

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
#include "entity.hpp"
#include "ObjectEntity.hpp"
#include "roomEntity.hpp"
#include "camera.hpp"
#include "singleton.hpp"
#include "skybox.hpp"
#include "config.hpp"
#include "shapeFactory.hpp"
#include "textureFactory.hpp"
#include "engineState.hpp"
#include "mathTypes.hpp"
#include "light.hpp"
#include "pointlight.hpp"
#include "terrainMap.hpp"
#include "timer.hpp"
#include "observerEntity.hpp"
#include "material.hpp"
#include "sprite.hpp"
#include "utils.hpp"
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

