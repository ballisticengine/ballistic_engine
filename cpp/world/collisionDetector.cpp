#include "world/collisionDetector.hpp"

CollsionInfo CollisionDetector::objectsCollide(PhysicalEntity *ea, PhysicalEntity *eb, Coords offset) {
   
   
    CollsionInfo ret;
    ret.collided = false;
    
    return ret;

}

CollsionInfo CollisionDetector::roomCollide(RoomEntity *r, PhysicalEntity *e, Coords offset) {
    CollsionInfo ci;
    return ci;
}

CollisionDetector::CollisionDetector() {

    broadphase = new btDbvtBroadphase();

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
            broadphase, solver, collisionConfiguration);

}

CollisionDetector::~CollisionDetector() {

}

void CollisionDetector::step(e_loc timediff) {
    //dynamicsWorld->stepSimulation(timediff);
    dynamicsWorld->performDiscreteCollisionDetection();
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
}

void CollisionDetector::addRoom(RoomEntity *room) {
    btTriangleMesh *mTriMesh = new btTriangleMesh();
    Shape *s = room->model;
    btVector3 *v;
    for (size_t i = 0; i < s->f_count; i++) {
        v = new btVector3[3];
        for (size_t n = 0; n < s->v_per_poly; n++) {
            Vector3d vertex = s->vertices[s->faces[i].index[n]];
            v[n] = btVector3(vertex.x, vertex.y, vertex.z);
        }
        mTriMesh->addTriangle(v[0], v[1], v[2]);
    }
    //collisionShapes.push_back(mTriMesh);
}

void CollisionDetector::addEntity(Entity *entity) {
    btCollisionShape* colShape = new btBoxShape(btVector3(
            entity->boundings[0]->width,
            entity->boundings[0]->height,
            entity->boundings[0]->depth));
    collisionShapes.push_back(colShape);
}