#include "world.hpp"

/*ent_list world::getEntities() {

}*/



skybox * world::getSkybox() {
	return this->sky;
}

obj_list world::getModels() {
	return this->getActiveRoom()->models;
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

void world::test() {
	cout << "Test world";
}

bool world::parseXml(string &fn) {
	string wd=fn;
	fn=fn+string(DS)+string("level.xml");
	shapeFactory *shapef=(shapeFactory *)shapeFactory::getInstance();
	textureFactory *texf=(textureFactory *)textureFactory::getInstance();
	texf->setWD(wd+DS+TEX_DIR);
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
	string skyfn= pt.get<string>("world.config.skybox");
	this->sky = new skybox(wd+DS+"textures"+DS+skyfn);

	//string tm_tex=pt.get<string>("world.config.terrain.map");
	//tm=new TerrainMap(tm_tex,tm_tex);
	//ptree& entities = pt.get_child("world.entities");

	ptree& world_jp=pt.get_child("world.config.jump_point");
	e_loc jx=world_jp.get<e_loc>("x"),
		jy=world_jp.get<e_loc>("y"),
		jz=world_jp.get<e_loc>("z"),
		rx=world_jp.get<e_loc>("rx"),
		ry=world_jp.get<e_loc>("ry"),
		rz=world_jp.get<e_loc>("rz");
	

	string gfn=wd+DS+"geometry.xml";

	/* Geometria poziomu */
	ptree gpt;
	read_xml(gfn, gpt, boost::property_tree::xml_parser::trim_whitespace);
	ptree &rooms=gpt.get_child("level");

	BOOST_FOREACH(const ptree::value_type &room, rooms) {

		faceTexShape *fs=shapef->getXML((ptree)room.second);
		roomEntity *roomE=new roomEntity();
		poly_list polys=fs->getPolys();
		
			roomE->ambient_light.r=room.second.get<e_loc>("ambient_light.r"),
			roomE->ambient_light.b=room.second.get<e_loc>("ambient_light.b"),
			roomE->ambient_light.g=room.second.get<e_loc>("ambient_light.g")
			;
		cout << "Ambient light: " << roomE->ambient_light.r << ", " << roomE->ambient_light.g << ", " << roomE->ambient_light.b << endl;
		roomE->setModel(fs);
		this->addRoomEntity(roomE);
		ptree &room_ents=(ptree)room.second.get_child("entities");
		BOOST_FOREACH(const ptree::value_type &entobj, room_ents) {
			string type=entobj.second.get<string>("type");
			e_loc x=entobj.second.get<float>("location.x"),y=entobj.second.get<float>("location.y"),
				z=entobj.second.get<float>("location.z"),rx=entobj.second.get<float>("facing.x"),
				ry=entobj.second.get<float>("facing.y"),rz=entobj.second.get<float>("facing.z");
			if (type=="object") {
				string mfn=wd+DS+MODEL_DIR+DS+entobj.second.get<string>("model"),
					tfn=entobj.second.get<string>("texture");
				e_loc sc=entobj.second.get<e_loc>("scale");
				shapef->setScale(sc);
				faceTexShape *shp=(faceTexShape *)shapef->get(mfn);
				texture *tex=(texture *)texf->get(tfn);
				Material *mat=new Material();
				ObjectEntity *oe=new ObjectEntity();
				shp->calculateNormals(); 
				oe->setModel(shp);
				oe->setMaterial(mat);
				oe->setTexture(tex);
				oe->locate(x,y,z);
				oe->setBoundingBox(new BoundingCube(oe->getModel()));
				
				oe->face(-90,0,0); //tymczasowo, i tak wiêkszoœæ obiektów potrzebuje dok³adnie takiego obrotu
				
				//oe->face(rx,ry,rz);
				roomE->addObjectEntity(oe);
			} else if(type=="light") {
				//cout << "Light " << x << ", " << y << ", " << z << endl ;	
				PointLight *l=new PointLight();
				l->locate(x,y,z);

				colorRGBA color;
				color.r=entobj.second.get<float>("r");
				color.g=entobj.second.get<float>("g");
				color.b=entobj.second.get<float>("b");
				color.a=1.0f;

				l->setAllColors(color);
				roomE->addLightEntity(l);
			} else if (type=="bounding") {
				
				e_loc 
					minx=entobj.second.get<float>("min.x"),
					miny=entobj.second.get<float>("min.y"),
					minz=entobj.second.get<float>("min.z"),
					maxx=entobj.second.get<float>("max.x"),
					maxy=entobj.second.get<float>("max.y"),
					maxz=entobj.second.get<float>("max.z")
					;
				cout << "Found bounding\n";
				cout << minx << ", " << miny << ", " << minz << ", " << maxx << ", " << maxy << ", " << maxz << endl;
				BoundingCube *bc=new BoundingCube(minx,miny,minz,maxx,maxy,maxz);
				roomE->boundings.push_back(bc);
				//roomE->setBoundingBox(bc);
			}

		}

	}
	observer.locate(jx,jy,jz);
	observer.face(rx,ry,rz);
	observer.setCamera(&default_camera);
	return true;
}

lights_list world::getLights() {
	return this->getActiveRoom()->lights;
}

void world::prepare() {

}

world::~world() {
	/*for(int i=0; i<this->entities.size(); i++) {
		// delete entities[i];
	}*/
}

camera *world::getCurrentCamera() {
	return &this->default_camera;
}

roomEntity * world::getActiveRoom() {
 return this->rooms[0];
}

void world::moveEntity(PhysicalEntity *e,time_int time_diff,bool skip_collision) {
	
	coords c=e->nextCoords(time_diff),x;
	x.translation=c.translation-e->getCoords().translation;

	rooms_list rl=this->getRooms();
	obj_list objs=this->getModels();
	BoundingCube *obc=e->getBoundingBox();

	MathTypes::vector cvec;
	
	if(!engineState::getInstance()->noclip) {
	/*
	 Kolizje z obiektami
	*/
	//c.translation.write();
	for(int i=0; i<objs.size(); i++) {
		cvec=objs[i]->collides(obc,c);
		if(cvec.x) {
			if(cvec.x<0) {
			c.translation.z=cvec.z-COLLISION_BACK;
			} else if(cvec.x>0) {
			c.translation.z=cvec.z+COLLISION_BACK;
			}
		}

		if(cvec.z) {
			//cout << cvec.x << endl;
			if(cvec.z<0) {
			c.translation.x=cvec.x-COLLISION_BACK;
			} else if(cvec.z>0) {
			c.translation.x=cvec.x+COLLISION_BACK;
			}
		}

		if(cvec.y) {
			//cvec.write();
			if(cvec.y<0) {
			c.translation.y=+COLLISION_BACK;
			} else {
			c.translation.y=-COLLISION_BACK;
			}
		}
	
	}
	
	/*
	Kolizje z poziomem
	*/
	for(int i=0; i<rl.size(); i++) {
		//break;
		cvec=rl[i]->collides(obc,c);
		//cvec.write();
		if(cvec.x) {
			c.translation.z=cvec.x;
		}

		if(cvec.z) {
			c.translation.x=cvec.z;
		}

		if(cvec.y) {
			c.translation.y=cvec.y;
		}
	}
	}
	
	e->translate(c);
	e->rotate(c.rotation.x,c.rotation.x,c.rotation.z);


}

void world::moveEntities() {
	e_loc x,y,z;
	x,y,z=0;
	obj_list things=this->getActiveRoom()->models;
	time_int lt=time.getDiffR();
	for(int i=0; i<things.size(); i++) {
		
		ObjectEntity *e=things[i];
		
		
		this->moveEntity((PhysicalEntity *)e,lt,false);
	}

	this->moveEntity((PhysicalEntity *)&this->observer,lt,false);
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

world * world::getInstance() {
	static world i;
	return &i;

}	

world & world::getRef() {
	return *world::getInstance();
}



void world::addRoomEntity(roomEntity *e) {
	this->rooms.push_back(e);
	//this->addEntity(e);
}
