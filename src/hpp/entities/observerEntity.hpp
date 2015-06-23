#ifndef OBSERVER_ENTITY_H
#define OBSERVER_ENTITY_H

#include "types/types.hpp"
#include "types/mathTypes.hpp"
#include "entities/physicalEntity.hpp"
#include "entities/Camera.hpp"
#include "entities/weapon.hpp"
#include "time/timer.hpp"

class ObserverMovement {
public:
    bool operator==(const ObserverMovement &m);
    bool forward, left, right, back, up, down, jump, next_weapon, prev_weapon;

    void reset();
};

class ObserverMouse {
public:
    bool left, right, middle, leftclick, rightclick, middleclick;
    bool operator==(const ObserverMouse &m);
    void reset();
};

class ObserverState {
public:
    ObserverMovement movement;
    ObserverMouse mouse;
    bool operator==(const ObserverState &s);

};

class ObserverEntity : public PhysicalEntity {
protected:
    Camera *cam;
    e_loc headbob_add, headbob_i, kickback;
    Timer bob_timer, kick_timer;
    ObserverState state, got_state;
    bool state_changed, lock;
    Camera dummy_camera;
public:

    Weapon *current_weapon;
    ObserverEntity();
    virtual ~ObserverEntity();

    virtual void setCamera(Camera *c);
    virtual Camera *getCamera();
    virtual void bobHead();
    virtual void kickBack(e_loc force);

    virtual ObserverState * getState();
    virtual void setState(ObserverState *state);
    virtual bool stateChanged();
    virtual void refreshState();

    virtual void translate(e_loc x, e_loc y, e_loc z);
    virtual void rotate(e_loc x, e_loc y, e_loc z);
    virtual void locate(e_loc x, e_loc y, e_loc z);
    virtual void face(e_loc x, e_loc y, e_loc z);



};

#endif