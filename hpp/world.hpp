

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
#include "objectEntity.hpp"
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

typedef vector <entity *> ent_list;
typedef vector <objectEntity *> obj_list;
typedef vector <roomEntity *> rooms_list;
typedef vector <light *> lights_list;

class world : public singleton<world> {
protected:
    ent_list entities;
	obj_list models;
	rooms_list rooms;
	lights_list lights;
    skybox *sky;
	camera default_camera;
   void moveEntities();
   clock_t last_tick;
public:
        ~world();
        ent_list getEntities();
		obj_list getModels();
		rooms_list getRooms();
		lights_list getLights();
        skybox * getSkybox();
		camera *getCurrentCamera();
        void makeTestWorld();
        bool parseXml(string &fn);
        void prepare();
		void operator()();
};

#endif	/* WORLD_HPP */

