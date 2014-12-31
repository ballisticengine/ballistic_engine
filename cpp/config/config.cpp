#include <bits/stl_pair.h>

#include "config/config.hpp"

config::config() {
   
    string fn=string(CONFIG_DIR)+string(DS)+string(CONFIG_FN);
    
    
    
   
	read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
	
	vd.width=pt.get<int>("config.screen.resx"); 
	vd.height=pt.get<int>("config.screen.resy");
	vd.frustum_start=pt.get<float>("config.screen.frustum_start");
	vd.frustum_end=pt.get<float>("config.screen.frustum_end");
	vd.frustum_x=pt.get<float>("config.screen.frustum_width");
	vd.frustum_y=pt.get<float>("config.screen.frustum_height");
	start_level=pt.get<string>("config.game.start_level");
        
        ptree scripts_xml=pt.get_child("config.scripts");
        BOOST_FOREACH(const ptree::value_type &script, scripts_xml) {
            string script_s=script.second.get_value<string>();
            scripts.push_back(script_s);
        }
	
}
        

videoData * config::getVD() {
 return &vd;
}

string & config::getStart() {
 return start_level;
}

ptree & config::getNode(string node) {
	return pt.get_child(node);
}

const ptree & config::getPtree() {
 return this->pt;
}

vector <string> config::getScripts() {
    return this->scripts;
}