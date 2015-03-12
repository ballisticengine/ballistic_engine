#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <iostream>

using namespace std;
using namespace boost::property_tree;

#include "misc/singleton.hpp"

#include "config/path.hpp"

#include "ui/hud.hpp"
#include "entities/weapon.hpp"
#include "entities/sprite.hpp"
#include "types/types.hpp"
#include "factories/shapeFactory.hpp"
#include "factories/textureFactory.hpp"
#include "ui/uiMesh.hpp"
#include "config/EngineState.hpp"

using boost::property_tree::ptree;

struct VideoData {
    int width, height, bpp;
    float frustum_start, frustum_end, frustum_x, frustum_y;
};



class Config : public Singleton<Config> {
    ptree pt;
    VideoData vd;
    string start_level;
    vector<string> scripts;
    void loadWeapons();

public:
    weapon_map available_weapons;
    string getRenderer();
    Config();
    VideoData * getVD();
    string & getStart();
    vector <string> getScripts();
    const ptree & getPtree();
    ptree & getNode(string node);

};

#endif	/* CONFIG_HPP */

