#include "world.hpp"

/*ent_list world::getEntities() {
	
}*/

skybox * world::getSkybox() {
    return this->sky;
}

obj_list world::getModels() {
	return this->models;
}

void world::makeTestWorld() {
    this->sky = new skybox("skybox.bmp");
}

bool world::parseXml(string &fn) {
	string wd=fn;
	fn=fn+string(DS)+string("level.xml");
	shapeFactory *shapef=(shapeFactory *)shapeFactory::getInstance();
	textureFactory *texf=(textureFactory *)textureFactory::getInstance();
	cout << "FN: " << fn << endl;
	using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn= pt.get<string>("world.config.skybox");
   cout << "}"<<skyfn << "}" << endl;
   this->sky = new skybox("data/"+skyfn);
   /*cout << "Loading models...\n";
   ptree& models = pt.get_child("world.models");
   BOOST_FOREACH(const ptree::value_type &v, models) {
	   string mfn=wd+string(DS)+v.second.get<string>("file");
	   e_loc sc=v.second.get<e_loc>("scale");
	   shapef->setScale(sc);
	   shapef->get(mfn);
	   
	   cout << "MODEL: " <<  mfn << ", " << "scale: " << sc << endl;

   } */
   ptree& entities = pt.get_child("world.entities");
   BOOST_FOREACH(const ptree::value_type &v, entities) {
	   e_loc x=v.second.get<float>("location.x"),y=v.second.get<float>("location.y"),
		   z=v.second.get<float>("location.z"),rx=v.second.get<float>("facing.x"),
		   ry=v.second.get<float>("facing.y"),rz=v.second.get<float>("facing.z");
	   string mfn=wd+DS+MODEL_DIR+DS+v.second.get<string>("model.file"),
		   tfn=wd+DS+TEX_DIR+DS+v.second.get<string>("model.texture");
	   e_loc sc=v.second.get<e_loc>("model.scale");
	   shapef->setScale(sc);
	   objectEntity *oe=new objectEntity();
	   shape *shp;
	   
	  // cout << x << ", " << y << ", " << z << endl;
	   shp=(shape *)shapef->get(mfn);
	   texture *tex=(texture *)texf->get(tfn);
	   oe->setModel(shp);
	   oe->setTexture(tex);
	   oe->locate(x,y,z);
	   oe->face(rx,ry,rz);
	   this->entities.push_back((entity *)oe);
	   this->models.push_back(oe);
   }
  return true;
}

world::~world() {
	for(int i=0; i<this->entities.size(); i++) {
	// delete entities[i];
	}
}