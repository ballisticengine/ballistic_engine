#include "entities/world.hpp"







TerrainMap * world::getTerrain() {
	return this->tm;
}





void world::prepare() {

}

world::world() {
	//this->scripting=PyScripting::getInstance();
}

world::~world() {
	cout << "World cleaning up..." << endl;
	deleteVector(rooms);
	
}

camera *world::getCurrentCamera() {
	return &this->default_camera;
}

roomEntity * world::getActiveRoom() {
 return this->rooms[0];
}

void world::moveEntity(PhysicalEntity *e,time_int time_diff,bool skip_collision) {
	
	
	coords c=e->nextCoords(time_diff),x;
	//cout << "SC: ";
	//c.translation.write();
	//TrRot v=e->getVelocity();
	bool movement=true;
	if((c.translation.x==0 && c.translation.y==0 && c.translation.z==0) && (c.rotation.x==0 && c.rotation.y==0 && c.rotation.z==0)) {
	 movement=false;
	}
	//c.translation.write();
	if(!movement) {
	 //return;
	}


	x.translation=c.translation-e->getCoords().translation;

	rooms_list rl=this->rooms;
	obj_list objs=this->active_room->models;
	BoundingCube *obc=e->getBoundingBox();

	MathTypes::vector cvec;
	bool lc=false;
	if(!engineState::getInstance()->noclip) {
	
	/*
	 Kolizje z obiektami
	*/

	size_t objs_size=objs.size();
	for(int i=0; i<objs_size; i++) {
		cvec=objs[i]->collides(e,c);
		
	/*if(cvec.x) {
		/if(cvec.x<0) {
			c.translation.z=cvec.z-COLLISION_BACK;
			} else if(cvec.x>0) {
			c.translation.z=cvec.z+COLLISION_BACK;
			}
			
			
		}

		if(cvec.z) {
			if(cvec.z<0) {
			c.translation.x=cvec.x-COLLISION_BACK;
			} else if(cvec.z>0) {
			c.translation.x=cvec.x+COLLISION_BACK;
			}
			
		}

		if(cvec.y) {
			if(cvec.y<0) {
			c.translation.y=+COLLISION_BACK;
			} else {
			c.translation.y=-COLLISION_BACK;
			}
			
		}
		*/
		
		if(cvec.x || cvec.y || cvec.z) {
                    lc=true;
			//e->setVelocity(v);
			//c=e->nextCoords(time_diff);
			//cout << "EC: ";
			//c.translation.write();
			PyScripting::getInstance()->broadcast("EntityCollision",(void *)e,(void *)objs[i],(void *)&cvec);
		} else {
			//PyScripting::getInstance()->broadcast("EntityMovement",(void *)e);
		}
	}
	
	/*
	Kolizje z poziomem
	*/
	size_t rl_size=rl.size();
	
        for(int i=0; i<rl_size; i++) {
		cvec=rl[i]->collides(e,c);
                
//                		if(cvec.x) {
//			c.translation.z=cvec.x;
//		}

		/*if(cvec.z) {
			c.translation.x=cvec.z;
		}

		if(cvec.y) {
			c.translation.y=cvec.y;
		}*/
//                if(cvec.y) {
//                    cvec.write();
//		}
		if(cvec.x || cvec.y || cvec.z) {
                    //c.translation.write();
                    lc=true;
                    PyScripting::getInstance()->broadcast("LevelCollision",(void *)e,(void *)rl[i],(void *)&cvec);
		}
	}
	}
	
	if(!lc) {
            e->translate(c);
            if(movement) {
                PyScripting::getInstance()->broadcast("EntityMovement",(void *)e);
            }
       } else {
            //cout << "LC";
        }
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

        if(observer.stateChanged()) {
            
           PyScripting::getInstance()->broadcast("ObserverStateChange",observer.getState());
        }
        
	this->moveEntity((PhysicalEntity *)&this->observer,lt,false);
}

void world::operator()() {

	//this->getActiveRoom()->model_animator.start();
	time.start();


	while(!engineState::getInstance()->exit()) {
		this->moveEntities(); 
	}
	//this->getActiveRoom()->model_animator.stop();

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
}
