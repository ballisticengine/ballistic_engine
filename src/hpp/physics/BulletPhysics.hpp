#ifndef COLLISIONDETECTOR_HPP
#define	COLLISIONDETECTOR_HPP

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>
#include <map>

#include "entities/ObjectEntity.hpp"
#include "entities/entity.hpp"
#include "entities/RoomEntity.hpp"
#include "types/mathTypes.hpp"


struct CollisionParty {
    Vector3d cvec,diff;
    string name;
    
};

struct CollisionInfo {
    CollisionParty A,B;
    bool collided;
    e_loc distance;
};




typedef map<Entity *,CollisionInfo> CiMap;
typedef vector<CollisionInfo> CiList;

class BulletPhysics {
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btCollisionWorld* dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    int numContacts;
    void transformEntity(Entity *entity, Vector3d v);
    Vector3d world_transform;
    CiMap collision_map;
public:
    void setWorldTransform(Vector3d world_transform);
    BulletPhysics();
    ~BulletPhysics();
    void addRoom(RoomEntity *room);
    void addEntity(Entity *entity);
    void step(e_loc timediff,rooms_list rooms);
    CollisionInfo objectsCollide(ObjectEntity *a, ObjectEntity *b, Coords offset);
    CollisionInfo roomCollide(RoomEntity *r, ObjectEntity *e, Coords offset);
    void rayTest(Vector3d origin, Vector3d direction);

};


#endif	

