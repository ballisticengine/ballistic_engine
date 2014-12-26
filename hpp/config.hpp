#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <iostream>

using namespace std;
using namespace boost::property_tree;

#include "singleton.hpp"

#define CONFIG_DIR "data"
#define SHADER_DIR "data/shaders"
#define LVL_DIR "levels" //w data/
#define DS "/"
#define CONFIG_FN "config.xml"
#define MODEL_DIR "models"
#define TEX_DIR "textures"
#define COMMON_DIR "data/common"

using boost::property_tree::ptree;

struct videoData {
    int width, height, bpp;
	float frustum_start, frustum_end, frustum_x, frustum_y;
};

class config : public singleton<config> {
	ptree pt;
	videoData vd;
	string start_level;

public:
    config();
	videoData * getVD();
	string & getStart();
	const ptree & getPtree();
	ptree & getNode(string node);
	 
};

#endif	/* CONFIG_HPP */

