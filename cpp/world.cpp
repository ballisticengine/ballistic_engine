#include "world.hpp"

/*ent_list world::getEntities() {
	
}*/

skybox * world::getSkybox() {
    return this->sky;
}

obj_list world::getModels() {
	return this->models;
}

rooms_list world::getRooms() {
	return this->rooms;
}

void world::makeTestWorld() {
    this->sky = new skybox("skybox.bmp");
}

TerrainMap * world::getTerrain() {
 return this->tm;
}

bool world::parseXml(string &fn) {
	string wd=fn;
	fn=fn+string(DS)+string("level.xml");
	shapeFactory *shapef=(shapeFactory *)shapeFactory::getInstance();
	textureFactory *texf=(textureFactory *)textureFactory::getInstance();
	texf->setWD(wd+DS+TEX_DIR);
	cout << "FN: " << fn << endl;
	using boost::property_tree::ptree;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    string skyfn= pt.get<string>("world.config.skybox");
   cout << "}"<<skyfn << "}" << endl;
   this->sky = new skybox(wd+DS+"textures"+DS+skyfn);
   
   string tm_tex=pt.get<string>("world.config.terrain.map");
   tm=new TerrainMap(tm_tex,tm_tex);

   ptree& entities = pt.get_child("world.entities");
  
   ptree& world_jp=pt.get_child("world.config.jump_point");
   e_loc jx=world_jp.get<e_loc>("x"),
	   jy=world_jp.get<e_loc>("y"),
	   jz=world_jp.get<e_loc>("z"),
	   rx=world_jp.get<e_loc>("rx"),
	   ry=world_jp.get<e_loc>("ry"),
	   rz=world_jp.get<e_loc>("rz");
   observer.locate(jx,jy,jz);
   observer.face(rx,ry,rz);
   observer.setCamera(&default_camera);
   
   string gfn=wd+DS+"geometry.xml";
   //cout << "GEOM FN: " << gfn << endl;
   //this->parseGeom(gfn);

   /* Geometria poziomu */
  ptree gpt;
  read_xml(gfn, gpt, boost::property_tree::xml_parser::trim_whitespace);
  ptree &rooms=gpt.get_child("level");
 
   
  BOOST_FOREACH(const ptree::value_type &room, rooms) {
	  //cout << room.first.c_str() << endl;
	
	  faceTexShape *fs=shapef->getXML((ptree)room.second);
	  roomEntity *roomE=new roomEntity();
	  
	  roomE->setModel(fs);
	  
	   this->entities.push_back((entity *)roomE);
	  
	   this->rooms.push_back(roomE);

	   ptree &room_ents=(ptree)room.second.get_child("entities");
	   BOOST_FOREACH(const ptree::value_type &entobj, room_ents) {
		   string type=entobj.second.get<string>("type");
		   e_loc x=entobj.second.get<float>("location.x"),y=entobj.second.get<float>("location.y"),
		   z=entobj.second.get<float>("location.z"),rx=entobj.second.get<float>("facing.x"),
		   ry=entobj.second.get<float>("facing.y"),rz=entobj.second.get<float>("facing.z");
		   cout << x << ", " << y << ", " << z << endl;
		   if (type=="object") {
				string mfn=wd+DS+MODEL_DIR+DS+entobj.second.get<string>("model"),
					 tfn=entobj.second.get<string>("texture");
				e_loc sc=entobj.second.get<e_loc>("scale");
				shapef->setScale(sc);
				shape *shp=(shape *)shapef->get(mfn);
				texture *tex=(texture *)texf->get(tfn);
				objectEntity *oe=new objectEntity();
				
				oe->setModel(shp);
				oe->setTexture(tex);
				oe->locate(x,y,z);
				oe->face(-90,0,0); //tymczasowo, i tak wiêkszoœæ obiektów potrzebuje dok³adnie takiego obrotu
				//oe->face(rx,ry,rz);
				this->entities.push_back((entity *)oe);
				this->models.push_back(oe);
		   } else if(type=="light") {
			 cout << "Light " << x << ", " << y << ", " << z << endl ;	
			 PointLight *l=new PointLight();
			 l->locate(x,y,z);
			 l->face(rx,ry,rz);
			 this->entities.push_back((entity *)l);
			 this->lights.push_back((light *)l);
		   }

	   }
	  
  }
   
   return true;
}

lights_list world::getLights() {
	return this->lights;
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

void world::moveEntity(PhysicalEntity *e) {
 time_int lt=time.getDiffR();
  coords c=e->nextCoords(lt);
e->translate(c);
e->rotate(c.rx,c.ry,c.rz);
}

void world::moveEntities() {
	e_loc x,y,z,lt;
	x,y,z=0;
	for(int i=0; i<this->models.size(); i++) {
		objectEntity *e=models[i];
		/*lt=time.getDiffR();
		coords c=e->nextCoords(lt);
		e->translate(c);*/
		this->moveEntity((PhysicalEntity *)e);
	}
	this->moveEntity((PhysicalEntity *)&this->observer);
}

void world::operator()() {
 
 time.start();

 while(!engineState::getInstance()->exit()) {
	 this->moveEntities(); 
 }

}

ObserverEntity * world::getObserver() {
	return &this->observer;
}

