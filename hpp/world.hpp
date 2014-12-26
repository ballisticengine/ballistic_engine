

#ifndef WORLD_HPP
#define	WORLD_HPP

#include <SDL/SDL.h>
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

typedef vector <roomEntity *> rooms_list;

class world {
protected:
	
	
	rooms_list rooms;
	
	

	skybox *sky;
	camera default_camera;
	ObserverEntity observer;
	void moveEntity(PhysicalEntity *e,time_int time_diff,bool skip_collision);
	void moveEntities();
	Timer time;
	TerrainMap *tm;
public:
	Sprite *testsprite;
	static world *getInstance(); 
	static world & getRef();
	~world();
	ent_list getEntities();
	obj_list getModels();
	//obj_reflist getModelsRef();
	rooms_list getRooms();
	lights_list getLights();
	skybox * getSkybox();
	camera *getCurrentCamera();
	void makeTestWorld();
	bool parseXml(string &fn);
	void prepare();
	void operator()();
	void test();
	roomEntity * getActiveRoom();
	ObserverEntity * getObserver();
	TerrainMap * getTerrain();

	
	void addRoomEntity(roomEntity *e);

};

#endif	/* WORLD_HPP */

