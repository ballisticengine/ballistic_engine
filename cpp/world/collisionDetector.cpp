#include "world/collisionDetector.hpp"

CollsionInfo CollisionDetector::objectsCollide(PhysicalEntity *ea, PhysicalEntity *eb, Coords offset) {
CollsionInfo ret;
    ret.collided = false;
    
    this->transformEntity(ea);
    this->transformEntity(eb);
    btCollisionObject *a,*b;
    a=(btCollisionObject *)ea->physics_data;
    b=(btCollisionObject *)eb->physics_data;
    
    
//    btCollisionAlgorithm* algo = dynamicsWorld->getDispatcher()->findAlgorithm(&objects[0],&objects[1]);
//        btManifoldResult contactPointResult(&objects[0],&objects[1]);
//        algo->processCollision(&objects[0],&objects[1],collisionWorld->getDispatchInfo(),&contactPointResult);
//       
//        btManifoldArray manifoldArray;
//        algo->getAllContactManifolds(manifoldArray);
//
//        int numManifolds = manifoldArray.size();

    
    dynamicsWorld->performDiscreteCollisionDetection();
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
    //cout << "MF: " << numManifolds << endl;
    for (int i = 0; i < numManifolds; i++) {
        btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = (btCollisionObject*) (contactManifold->getBody0());
        btCollisionObject* obB = (btCollisionObject*) (contactManifold->getBody1());
        contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
        numContacts = contactManifold->getNumContacts();
        for (int j = 0; j < numContacts; j++) {
            //Get the contact information
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            btVector3 ptA = pt.getPositionWorldOnA();
            btVector3 ptB = pt.getPositionWorldOnB();
            double ptdist = pt.getDistance();
            cout << "Dist:" << ptdist << endl;
        }
    }
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
    //dynamicsWorld->setGravity(btVector3(0.0, 0.0, 0.0));

}

CollisionDetector::~CollisionDetector() {

}

void CollisionDetector::step(e_loc timediff) {
    //dynamicsWorld->stepSimulation(timediff);


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

void CollisionDetector::transformEntity(Entity *entity) {
    btTransform btt;
    Coords c = entity->getCoords();
    btCollisionObject *body = (btCollisionObject*)entity->physics_data;
    //body->getMotionState()->getWorldTransform(btt);
    btt.setIdentity();
    btt.setOrigin(btVector3(c.translation.x, c.translation.y, c.translation.z));
    body->setWorldTransform(btt);
    body->forceActivationState(DISABLE_DEACTIVATION);
    //body->getMotionState()->setWorldTransform(btt);
    //body->setCenterOfMassTransform(btt);
}

void CollisionDetector::addEntity(Entity *entity) {

    cout << "Adding to CE: " << entity->name << endl;
    Coords c=entity->getCoords();
    btCollisionShape* colShape = new btBoxShape(btVector3(entity->boundings[0]->width,
            entity->boundings[0]->height,
            entity->boundings[0]->depth
           ));
     cout << entity->boundings[0]->width << ", "
             << entity->boundings[0]->height << ", "
             << entity->boundings[0]->depth
             << endl;
    btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    
    btCollisionObject *body = new btCollisionObject();
    body->setCollisionShape(colShape);
    entity->physics_data=(void *)body;
    dynamicsWorld->addCollisionObject(body);
    this->transformEntity(entity);
    btTransform abt;
    btVector3 min,max;
    
//    colShape->getAabb(abt,min,max);
//    entity->boundings[0]=new BoundingCube(min.x(),
//            min.y(),
//            min.z(),
//            max.x(),
//            max.y(),
//            max.z());
//    
    
    
    //collisionShapes.push_back(colShape);
}