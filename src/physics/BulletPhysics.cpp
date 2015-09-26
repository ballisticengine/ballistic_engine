#include "physics/BulletPhysics.hpp"

//TODO: use offset to prevent from 'jumping'

CollisionInfo BulletPhysics::objectsCollide(ObjectEntity *ea, ObjectEntity *eb, Coords offset) {
    CollisionInfo ci;
    ci.collided = false;
    static unsigned long cc = 0;

    this->transformEntity(ea, offset.translation);
    this->transformEntity(eb, Vector3d(0, 0, 0));


    btCollisionObject *a = (btCollisionObject *) (ea->physics_data),
            *b = (btCollisionObject *) (eb->physics_data)
            ;

    dynamicsWorld->performDiscreteCollisionDetection();
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
    //cout << "MF: " << numManifolds << endl;
    for (int i = 0; i < numManifolds; i++) {
        btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = (btCollisionObject*) (contactManifold->getBody0());
        btCollisionObject* obB = (btCollisionObject*) (contactManifold->getBody1());
        Entity *a = (Entity *) obA->getUserPointer(),
                *b = (Entity *) obB->getUserPointer();

        if (!(a == ea && b == eb)) {
            continue;
        }
        contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
        numContacts = contactManifold->getNumContacts();
        for (int j = 0; j < numContacts; j++) {
            //Get the contact information
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            btVector3 ptA = pt.getPositionWorldOnA();
            btVector3 ptB = pt.getPositionWorldOnB();
            double ptdist = pt.getDistance();
            //            if (ptdist>0) {
            //                 ci.collided=false;
            //            } else {
            //               ci.collided=true; 
            //            }

            ci.A.name = a->name;
            ci.B.name = b->name;
            ci.A.cvec.x = ptA.x();
            ci.A.cvec.y = ptA.y();
            ci.A.cvec.z = ptA.z();
            ci.B.cvec.x = ptB.x();
            ci.B.cvec.y = ptB.y();
            ci.B.cvec.z = ptB.z();
            ci.A.diff = ci.B.cvec - ci.A.cvec;
            ci.B.diff = ci.A.cvec - ci.B.cvec;
            ci.collided = true;
            ci.distance = ptdist;
            //cc++;
            //cout << a->name << ", " << b->name << ", Dist:" << ptdist << ", " << cc << endl;
        }
    }
    this->transformEntity(ea, -offset.translation);
    return ci;

}

CollisionInfo BulletPhysics::roomCollide(RoomEntity *r, ObjectEntity *e, Coords offset) {

    return this->objectsCollide(e, r, offset);
}

void BulletPhysics::setWorldTransform(Vector3d world_transform) {
    this->world_transform = world_transform;
}

BulletPhysics::BulletPhysics() {

    broadphase = new btDbvtBroadphase();

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
            broadphase, solver, collisionConfiguration);
    //dynamicsWorld->setGravity(btVector3(0.0, 0.0, 0.0));

}

BulletPhysics::~BulletPhysics() {

}

void BulletPhysics::step(e_loc timediff, rooms_list rooms) {


}

void BulletPhysics::addRoom(RoomEntity *room) {
    cout << "addRoom" << endl;
    btTriangleMesh *mTriMesh = new btTriangleMesh();
    Shape *s = room->model;
    btVector3 *v;
    for (size_t i = 0; i < s->f_count; i++) {
        v = new btVector3[3];
        for (size_t n = 0; n < s->v_per_poly; n++) {
            Vector3d vertex = s->vertices[s->faces[i].index[n]];
            v[n] = btVector3(-vertex.x, -vertex.y, -vertex.z);
        }
        mTriMesh->addTriangle(v[0], v[1], v[2]);
    }
    btCollisionObject *body = new btCollisionObject();
    room->physics_data = (void *) body;

    body->setCollisionShape(new btBvhTriangleMeshShape(mTriMesh, false));

    body->setUserPointer((void *) room);
    dynamicsWorld->addCollisionObject(body);
    this->transformEntity(room, Vector3d(0, 0, 0));
    //collisionShapes.push_back(mTriMesh);
}

void BulletPhysics::transformEntity(Entity *entity, Vector3d v) {
    btTransform btt;
    Coords ec = entity->getCoords(), c;
    btCollisionObject *body = (btCollisionObject*) entity->physics_data;
    //body->getMotionState()->getWorldTransform(btt);
    btt.setIdentity();
    c.translation = ec.translation;
    if (entity->parent) {
        Coords pc = entity->parent->getCoords();
        c.translation = c.translation; //+pc.translation;
    }

    //TODO: proper checking
    if (entity->name == "observer") {
        //v.write();
        btt.setOrigin(btVector3(c.translation.x + v.x, c.translation.y + v.y, c.translation.z + v.z));
    } else if (entity->name == "Room1") {
        //btt.setOrigin(btVector3(c.translation.x, c.translation.y, -c.translation.z));
        btt.setOrigin(btVector3(-c.translation.x, -c.translation.y, -c.translation.z));
    } else {
        btt.setOrigin(btVector3(-c.translation.x, -c.translation.y, -c.translation.z));
    }
    body->setWorldTransform(btt);
    body->forceActivationState(DISABLE_DEACTIVATION);
    //body->getMotionState()->setWorldTransform(btt);
    //body->setCenterOfMassTransform(btt);
}

void BulletPhysics::addEntity(Entity *entity) {

    cout << "Adding to CE: " << entity->name << endl;
    Coords c = entity->getCoords();
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
    entity->physics_data = (void *) body;

    body->setCollisionShape(colShape);
    body->setUserPointer((void *) entity);

    dynamicsWorld->addCollisionObject(body);
    this->transformEntity(entity, Vector3d(0, 0, 0));
    btTransform abt;
    btVector3 min, max;

    colShape->getAabb(abt, min, max);
    btVector3 bt = body->getWorldTransform().getOrigin();
    entity->boundings[0] = new BoundingCube(
            bt.x() + min.x(),
            bt.y() + min.y(),
            bt.z() + min.z(),
            bt.x() + max.x(),
            bt.y() + max.y(),
            bt.z() + max.z());
    //Źle ustawia bryły brzegowe w bullet
    //    


    //collisionShapes.push_back(colShape);
}

void BulletPhysics::rayTest(Vector3d origin, Vector3d direction) {
    direction = direction * 1000.0f;

    btCollisionWorld::ClosestRayResultCallback RayCallback(
            btVector3(origin.x, origin.y, origin.z),
            btVector3(direction.x, direction.y, direction.z)
            );
    dynamicsWorld->rayTest(
            btVector3(origin.x, origin.y, origin.z),
            btVector3(direction.x, direction.y, direction.z),
            RayCallback
            );
    if(RayCallback.hasHit()) {
        cout << "Ray has hit" << endl;
    }
}