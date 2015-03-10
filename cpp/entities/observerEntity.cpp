#include "entities/observerEntity.hpp"

bool ObserverMovement::operator==(const ObserverMovement &m) {

    if (m.forward == forward && m.back == back && m.left == left && m.right == right && m.up == up && m.down == down) { //
        return true;
    }
    return false;
}

void ObserverMovement::reset() {
    forward = back = left = right = up = down = false;
}

void ObserverMouse::reset() {
    leftclick = rightclick = middleclick = left = right = middle = 0;
}

bool ObserverMouse::operator==(const ObserverMouse &m) {
    if (m.left == left && m.right == right && m.middle == middle) {
        return true;
    }
    return false;
}

bool ObserverState::operator==(const ObserverState &s) {
    if (movement == s.movement && mouse == s.mouse) {
        return true;
    }
    return false;
}
///////////

void ObserverEntity::setCamera(Camera *c) {
    this->cam = c;

}

void ObserverEntity::translate(e_loc x, e_loc y, e_loc z) { //tu podejżane (bo w Entity jest duplikacja)
    this->x += x;
    this->y += y;
    this->z += z;
   
        boundings[0]->max.x += x;
        boundings[0]->max.y += y;
        boundings[0]->max.z += z;
        boundings[0]->min.x += x;
        boundings[0]->min.y += y;
        boundings[0]->min.z += z;
        boundings[0]->loc.x = this->x;
        boundings[0]->loc.y = this->y;
        boundings[0]->loc.z = this->z;
   
    this->cam->translate(x, y, z);
}

void ObserverEntity::locate(e_loc x, e_loc y, e_loc z) {
    this->x = x;
    this->y = y;
    this->z = z;
    
        boundings[0]->max.x += x;
        boundings[0]->max.y += y;
        boundings[0]->max.z += z;
        boundings[0]->min.x += x;
        boundings[0]->min.y += y;
        boundings[0]->min.z += z;
        boundings[0]->loc.x = this->x;
        boundings[0]->loc.y = this->y;
        boundings[0]->loc.z = this->z;
    
    this->cam->locate(x, y, z);

}

void ObserverEntity::bobHead() {
    //	if(bob_timer.getDiffR()==0.0) {
    //	 cout <<bob_timer.getDiffR() << endl;
    //		return;
    //	}


    // headbob_i+=80*bob_timer.getDiffR();
    // headbob_add=sin(headbob_i)*2;

}

void ObserverEntity::kickBack(e_loc force) {
    cout << "Kickback";
    lock=true;
    this->cam->rotate(90,0,0);
    lock=false;
}

void ObserverEntity::rotate(e_loc x, e_loc y, e_loc z) {
    if(lock) {
        return;
    }
    Entity::rotate(x, y, z);
    this->cam->rotate(x, y, z);
}

void ObserverEntity::face(e_loc x, e_loc y, e_loc z) {
    if(lock) {
        return;
    }
    
    Entity::face(x, y, z);
    this->cam->face(x, y, z);
}

Camera * ObserverEntity::getCamera() {

    cam->locate(x, y - boundings[0]->height / 2, z);
    //cam->face(rx,ry,rz);

    return this->cam;
}

ObserverEntity::ObserverEntity() {
    boundings.push_back(new BoundingCube(7, 30, 7));
    headbob_i = 0;
    bob_timer.getDiffR();
    this->cam = cam;
    lock=false;
}

ObserverEntity::~ObserverEntity() {
    //delete this->cam;
}

ObserverState * ObserverEntity::getState() {
    //this->state_changed=false;


    return &this->state;
}

void ObserverEntity::setState(ObserverState * state) {



    this->state = *state;

}

bool ObserverEntity::stateChanged() {
    bool c = this->state_changed;
    this->state_changed = false;
    return c;



}

void ObserverEntity::refreshState() {
    this->state_changed = true;
}