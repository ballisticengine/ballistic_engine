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
#define DS "/"
#define CONFIG_FN "config.xml"
struct videoData {
    int width, height, bpp;
	float frustum_start, frustum_end, frustum_x, frustum_y;

};
class config : public singleton<config> {

	videoData vd;
	string start_level;

public:
    config();
	videoData * getVD();
	string & getStart();
	 
};

#endif	/* CONFIG_HPP */

