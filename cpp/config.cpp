#include "config.hpp"

config::config() {
   
    string fn=string(CONFIG_DIR)+string(DS)+string(CONFIG_FN);
    
    using boost::property_tree::ptree;
    ptree pt;
   
	read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
	
	vd.width=pt.get<int>("config.screen.resx"); 
	vd.height=pt.get<int>("config.screen.resy");
	vd.frustum_start=pt.get<float>("config.screen.frustum_start");
	vd.frustum_end=pt.get<float>("config.screen.frustum_end");
	vd.frustum_x=pt.get<float>("config.screen.frustum_width");
	vd.frustum_y=pt.get<float>("config.screen.frustum_height");
	start_level=pt.get<string>("config.game.start_level");
	
}
        

videoData * config::getVD() {
 return &vd;
}

string & config::getStart() {
 return start_level;
}