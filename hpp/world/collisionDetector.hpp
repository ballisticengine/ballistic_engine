#ifndef COLLISIONDETECTOR_HPP
#define	COLLISIONDETECTOR_HPP

#include <BulletDynamics/btBulletDynamicsCommon.h>

#include "entities/physicalEntity.hpp"
#include "entities/entity.hpp"
#include "entities/RoomEntity.hpp"
#include "types/mathTypes.hpp"


struct CollsionInfo {
    Vector3d cvec;
    string nameA,nameB;
    bool collided;
};


class CollisionDetector {
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    int numContacts;
    void transformEntity(Entity *entity);
public:
    CollisionDetector();
    ~CollisionDetector();
    void addRoom(RoomEntity *room);
    void addEntity(Entity *entity);
    void step(e_loc timediff);
    CollsionInfo objectsCollide(PhysicalEntity *a, PhysicalEntity *b, Coords offset);
    CollsionInfo roomCollide(RoomEntity *r, PhysicalEntity *e, Coords offset);

};


#endif	

