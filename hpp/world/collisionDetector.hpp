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
    Vector3d cTest(BoundingCube *a, BoundingCube *b, Coords offset);
    bool hitTest(BoundingCube *a, BoundingCube *b, Vector3d offset);
    bool roomHitTest(BoundingCube *a, BoundingCube *b, Vector3d offset);
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
public:
    CollisionDetector();
    ~CollisionDetector();
    void addRoom(RoomEntity *room);
    CollsionInfo objectsCollide(PhysicalEntity *a, PhysicalEntity *b, Coords offset);
    CollsionInfo roomCollide(RoomEntity *r, PhysicalEntity *e, Coords offset);

};


#endif	

