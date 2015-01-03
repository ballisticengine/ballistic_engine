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
	
        HUD *hud=HUD::getInstance();
        ptree hud_xml=pt.get_child("config.screen.hud");
        BOOST_FOREACH(const ptree::value_type &image, hud_xml) {
            string 
                name=image.second.get<string>("name"),
                texname=image.second.get<string>("texture")    
                    ;
            e_loc 
                width=image.second.get<e_loc>("width"),
                height=image.second.get<e_loc>("height"),
                    x=image.second.get<e_loc>("x"),
                    y=image.second.get<e_loc>("y")
                    ;
            
            hud->addImage(texname,name,width,height,x,y);
            
        }
//        UiImage *img1,*img2;
//        img1=hud->getImage("test");
//        img2=hud->getImage("test2");
        //img1->tex->setPixels(img2->tex->getPixels());
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