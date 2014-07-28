

#ifndef WORLD_HPP
#define	WORLD_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

using namespace std;
using namespace boost::property_tree;
#include "entity.hpp"
#include "singleton.hpp"
#include "skybox.hpp"


typedef vector <entity *> ent_list;

class world : public singleton<world> {
protected:
    ent_list entities;
    skybox *sky;
    public:
        
        ent_list getEntities();
        skybox * getSkybox();
        void makeTestWorld();
        bool parseXml(const string &fn);
        void prepare();
};

#endif	/* WORLD_HPP */

