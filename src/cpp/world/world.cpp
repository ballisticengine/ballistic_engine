#include "world/World.hpp"



void World::prepare() {

}

World::World() {

    //this->scripting=PyScripting::getInstance();
    moving_lock = false;
}

World::~World() {
    cout << "World cleaning up..." << endl;
    deleteVector3d(rooms);

}

Camera *World::getCurrentCamera() {
    return &this->default_Camera;
}

RoomEntity * World::getActiveRoom() {
    return this->rooms[0];
}

void World::moveEntity(ObjectEntity *e, time_int time_diff, bool skip_collision) {


    Coords c = e->nextCoords(time_diff), x;
    bool movement = true;
    if ((c.translation.x == 0 && c.translation.y == 0 && c.translation.z == 0) && (c.rotation.x == 0 && c.rotation.y == 0 && c.rotation.z == 0)) {
        movement = false;
    }


   

    rooms_list rl = this->rooms;
    obj_list objs = this->active_room->models;
    BoundingCube *obc = e->getBoundingBox();

    Vector3d cvec;
    bool lc = false;
    if (!EngineState::getInstance()->getBool("noclip") && !e->no_collisions) {

        /*
         Kolizje z obiektami
         */

        size_t objs_size = objs.size();
        for (int i = 0; i < objs_size; i++) {
            if (e == objs[i]) {
                break;
            }
            CollisionInfo ci = collisions.objectsCollide(objs[i], e, c); //objs[i]->collides(e, c);
            //cvec=ci.cvec;


            if (ci.collided) {
                lc = true;

                PyScripting::getInstance()->broadcast("EntityCollision", (void *) e, (void *) objs[i], (void *) &ci);
            } else {
                //PyScripting::getInstance()->broadcast("EntityMovement",(void *)e);
            }
        }

        /*
        Kolizje z poziomem
         */
       
        size_t rl_size = rl.size();
        CollisionInfo ci;
        for (int i = 0; i < rl_size; i++) {
            ci = collisions.roomCollide(rl[i], e, c); //rl[i]->collides(e, c);
            
            if (ci.collided) {
                lc=true;
                PyScripting::getInstance()->broadcast("LevelCollision", (void *) e, (void *) rl[i], (void *) &ci);
                
            } 
        }
    }
    //TODO move this to python or stick with c++ only for collisions
//    if (!lc) {
        e->translate(c); 
        if (movement) {
            PyScripting::getInstance()->broadcast("EntityMovement", (void *) e);
        }
//    }
    e->rotate(c.rotation.x, c.rotation.x, c.rotation.z);



}

void World::moveEntities() {

    e_loc x, y, z;
    x, y, z = 0;
    obj_list things = this->getActiveRoom()->models;
    time_int lt = time.getDiffR();
    collisions.step(lt, rooms);
    for (int i = 0; i < things.size(); i++) {

        ObjectEntity *e = things[i];
         this->moveEntity((ObjectEntity *) e, lt, false);

    }



    this->moveEntity((ObjectEntity *) & this->observer, lt, false);
}

void World::operator()() {

    //this->getActiveRoom()->model_animator.start();
    time.start();

    int n = 0;
    while (!EngineState::getInstance()->getBool("exit")) {


        this->moveEntities();

    }
    //this->getActiveRoom()->model_animator.stop();

}

ObserverEntity * World::getObserver() {
    return &this->observer;
}

World * World::getInstance() {
    static World i;
    return &i;

}

World & World::getRef() {
    return *World::getInstance();
}

void World::addRoomEntity(RoomEntity *e) {
    this->rooms.push_back(e);
}

 BulletPhysics World::getPhysicsEngine() {
     return this->collisions;
 }