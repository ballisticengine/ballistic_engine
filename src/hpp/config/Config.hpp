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
#include "resources/ResourceManager.hpp"
#include "ui/uiMesh.hpp"
#include "config/EngineState.hpp"
#include "config/KeyBindings.hpp"

using boost::property_tree::ptree;

struct VideoData {
    int width, height, bpp;
    float frustum_start, frustum_end, frustum_x, frustum_y;
};


/* 
 * Note, actually
 * Engine state = config
 * Config = config loader
 */
class Config : public Singleton<Config> {
protected:    
    ptree pt;
    VideoData vd;
    string start_level;
    vector<string> scripts;
    void loadWeapons();
    KeyBindings *key_bindings;

public:
    weapon_map available_weapons;
    string getRenderer();
    Config();
    VideoData * getVD();
    string & getStart();
    vector <string> getScripts();
    const ptree & getPtree();
    ptree & getNode(string node);
    KeyBindings *getKeyBindings();
    void setKeyBindings(KeyBindings *key_bindings);
    //destructor (clean keybindings and whatnot)
};

#endif	/* CONFIG_HPP */

