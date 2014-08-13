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
   ptree& world_jp=pt.get_child("world.config.jump_point");
   e_loc jx=world_jp.get<e_loc>("x"),
	   jy=world_jp.get<e_loc>("y"),
	   jz=world_jp.get<e_loc>("z"),
	   rx=world_jp.get<e_loc>("rx"),
	   ry=world_jp.get<e_loc>("ry"),
	   rz=world_jp.get<e_loc>("rz");
   default_camera.locate(jx,jy,jz);
   default_camera.face(rx,ry,rz);
   string gfn=wd+DS+"geometry.xml";
   //cout << "GEOM FN: " << gfn << endl;
   //this->parseGeom(gfn);

   /* Geometria poziomu */
  ptree gpt;
  read_xml(gfn, gpt, boost::property_tree::xml_parser::trim_whitespace);
  ptree &rooms=gpt.get_child("level");
 
   
  BOOST_FOREACH(const ptree::value_type &room, rooms) {
	  XMLShapeInfo xsi=shapef->getXML((ptree)room.second);
	  roomEntity *roomE=new roomEntity();
	  string ttfn=wd+DS+TEX_DIR+DS+xsi.tex_fn;
	  roomE->setModel(xsi.s);
	  cout << "T: " << xsi.tex_fn << endl;
	  texture *tex=(texture *)texf->get(ttfn);
	  roomE->setTexture(tex);
	   this->entities.push_back((entity *)roomE);
	   this->models.push_back((objectEntity *)roomE);
	  
  }
   
   return true;
}

bool world::parseGeom(string fn) {
  shapeFactory *sf=shapeFactory::getInstance();
  textureFactory *texf=(textureFactory *)textureFactory::getInstance();
  ptree pt;
  read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
  ptree &rooms=pt.get_child("level");
  
  BOOST_FOREACH(const ptree::value_type &room, rooms) {
	  XMLShapeInfo xsi=sf->getXML((ptree)room.second);
	  roomEntity *roomE=new roomEntity();
	  roomE->setModel(xsi.s);
	  
	  //texture *tex=(texture *)texf->get(tfn);
	  //roomE->setTexture();
  }
  return true;
}

void world::prepare() {
	
}

world::~world() {
	for(int i=0; i<this->entities.size(); i++) {
	// delete entities[i];
	}
}

camera *world::getCurrentCamera() {
 return &this->default_camera;
}