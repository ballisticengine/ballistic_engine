#include "world.hpp"

/*ent_list world::getEntities() {
	
}*/

skybox * world::getSkybox() {
    return this->sky;
}

void world::makeTestWorld() {
    this->sky = new skybox("skybox.bmp");
}

bool world::parseXml(const string &fn) {
	shapeFactory *shapef=shapeFactory::getInstance();
	cout << "FN: " << fn << endl;
	using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn= pt.get<string>("world.config.skybox");
   cout << "}"<<skyfn << "}" << endl;
   this->sky = new skybox("data/"+skyfn);
   cout << "X" << endl;
   ptree& models = pt.get_child("world.models");
   BOOST_FOREACH(const ptree::value_type &v, models) {
	   string mfn=v.second.get<string>("file");
	   cout << "MODEL: " <<  mfn << endl;

   } 
   ptree& entities = pt.get_child("world.entities");
   BOOST_FOREACH(const ptree::value_type &v, entities) {
       //cout << v.second.get<string>("name") << endl; //this is wrong
       
   }
  return true;
}
