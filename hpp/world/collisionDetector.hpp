#ifndef COLLISIONDETECTOR_HPP
#define	COLLISIONDETECTOR_HPP

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>
#include <map>

#include "entities/physicalEntity.hpp"
#include "entities/entity.hpp"
#include "entities/RoomEntity.hpp"
#include "types/mathTypes.hpp"


struct CollsionInfo {
    Vector3d cvec;
    string nameA,nameB;
    bool collided;
};


typedef map<Entity *,CollsionInfo> CiMap;
typedef vector<CollsionInfo> CiList;

class CollisionDetector {
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btCollisionWorld* dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    int numContacts;
    void transformEntity(Entity *entity);
    Vector3d world_transform;
    CiMap collision_map;
public:
    void setWorldTransform(Vector3d world_transform);
    CollisionDetector();
    ~CollisionDetector();
    void addRoom(RoomEntity *room);
    void addEntity(Entity *entity);
    void step(e_loc timediff,rooms_list rooms);
    CollsionInfo objectsCollide(PhysicalEntity *a, PhysicalEntity *b, Coords offset);
    CollsionInfo roomCollide(RoomEntity *r, PhysicalEntity *e, Coords offset);

};


#endif	

