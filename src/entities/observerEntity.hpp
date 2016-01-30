#ifndef OBSERVER_ENTITY_H
#define OBSERVER_ENTITY_H

#include "types/types.hpp"
#include "types/Vector3d.hpp"
#include "entities/ObjectEntity.hpp"
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

class ObserverEntity : public ObjectEntity {
protected:
    Camera *cam;
    scalar_t headbob_add, headbob_i, kickback;
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
    virtual void kickBack(scalar_t force);

    virtual ObserverState * getState();
    virtual void setState(ObserverState *state);
    virtual bool stateChanged();
    virtual void refreshState();

    virtual void translate(scalar_t x, scalar_t y, scalar_t z);
    virtual void rotate(scalar_t x, scalar_t y, scalar_t z);
    virtual void locate(scalar_t x, scalar_t y, scalar_t z);
    virtual void face(scalar_t x, scalar_t y, scalar_t z);



};

#endif