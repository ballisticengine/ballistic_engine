#include "entities/observerEntity.hpp"



bool ObserverMovement::operator==(const ObserverMovement &m) {
    
    if(m.forward==forward && m.back==back && m.left==left && m.right==right && m.up==up && m.down==down) { //
        return true;
    }
    return false;
}

 void ObserverMovement::reset() {
     forward=back=left=right=up=down=false;
 }

bool  ObserverMouse::operator==(const ObserverMouse &m) {
    if (m.left==left && m.right==right && m.middle==middle) {
        return true;
    }
    return false;
}

bool ObserverState::operator==(const ObserverState &s) {
    if (movement==s.movement) {
        return true;
    } 
    return false;
}
///////////


void ObserverEntity::setCamera(camera *c) {
	this->cam=c;
	
}

void ObserverEntity::translate(e_loc x,e_loc y,e_loc z) {
 this->x+=x;
 this->y+=y;
 this->z+=z;
 if(this->bounding_box) {
	 this->bounding_box->max.x+=x;
	 this->bounding_box->max.y+=y;
	 this->bounding_box->max.z+=z;
	 this->bounding_box->min.x+=x;
	 this->bounding_box->min.y+=y;
	 this->bounding_box->min.z+=z;
	 this->bounding_box->loc.x=this->x;
	 this->bounding_box->loc.y=this->y;
	 this->bounding_box->loc.z=this->z;
 }
 this->cam->translate(x,y,z);
}



void ObserverEntity::locate(e_loc x,e_loc y,e_loc z) {
 this->x=x;
 this->y=y;
 this->z=z;
 if(this->bounding_box) { //todo: bez kopiuj wklej
	 this->bounding_box->max.x+=x;
	 this->bounding_box->max.y+=y;
	 this->bounding_box->max.z+=z;
	 this->bounding_box->min.x+=x;
	 this->bounding_box->min.y+=y;
	 this->bounding_box->min.z+=z;
	 this->bounding_box->loc.x=this->x;
	 this->bounding_box->loc.y=this->y;
	 this->bounding_box->loc.z=this->z;
 }
	this->cam->locate(x,y,z);

}

void ObserverEntity::bobHead() {
//	if(bob_timer.getDiffR()==0.0) {
//	 cout <<bob_timer.getDiffR() << endl;
//		return;
//	}
	
    
// headbob_i+=80*bob_timer.getDiffR();
// headbob_add=sin(headbob_i)*2;
 
}



void ObserverEntity::rotate(e_loc x,e_loc y, e_loc z) {
	
	this->cam->rotate(x,y,z);
}



void ObserverEntity::face(e_loc x,e_loc y,e_loc z) {
	entity::face(x,y,z);
	this->cam->face(x,y,z);
}

camera * ObserverEntity::getCamera() {
 
 cam->locate(x,y-bounding_box->height/2,z);
 //cam->face(rx,ry,rz);
 
 return this->cam;
}



ObserverEntity::ObserverEntity() {
	this->bounding_box=new BoundingCube(7,30,7);
	headbob_i=0;
	bob_timer.getDiffR();
	this->cam=cam;
}

ObserverEntity::~ObserverEntity() {
	//delete this->cam;
}

ObserverState * ObserverEntity::getState() {
    //this->state_changed=false;
    
    
    return &this->state;
}

void ObserverEntity::setState(ObserverState * state) {
   
    
   
    this->state=*state;

}

bool ObserverEntity::stateChanged() {
    bool c=this->state_changed;
    this->state_changed=false;
    return c;
    
    
    
}

void ObserverEntity::refreshState() {
    this->state_changed=true;
}