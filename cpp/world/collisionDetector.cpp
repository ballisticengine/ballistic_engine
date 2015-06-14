#include "world/collisionDetector.hpp"

CollsionInfo CollisionDetector::objectsCollide(PhysicalEntity *ea, PhysicalEntity *eb, Coords offset) {
    CollsionInfo ret;
    ret.collided = false;
    static unsigned long cc = 0;
    this->transformEntity(ea);

    this->transformEntity(eb);


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
        CollsionInfo ci;
        for (int j = 0; j < numContacts; j++) {
            //Get the contact information
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            btVector3 ptA = pt.getPositionWorldOnA();
            btVector3 ptB = pt.getPositionWorldOnB();
            double ptdist = pt.getDistance();



            ci.nameA = a->name;
            ci.nameB = b->name;
            //            ci.collided=true;
            cc++;
            cout << a->name << ", " << b->name << ", Dist:" << ptdist << ", " << cc << endl;
        }
    }

    return ret;

}

CollsionInfo CollisionDetector::roomCollide(RoomEntity *r, PhysicalEntity *e, Coords offset) {

    return this->objectsCollide(e, r, offset);
}

void CollisionDetector::setWorldTransform(Vector3d world_transform) {
    this->world_transform = world_transform;
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

void CollisionDetector::step(e_loc timediff, rooms_list rooms) {





}

void CollisionDetector::addRoom(RoomEntity *room) {
    cout << "addRoom" << endl;
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
    btCollisionObject *body = new btCollisionObject();
    room->physics_data = (void *) body;

    body->setCollisionShape(new btBvhTriangleMeshShape(mTriMesh, false));

    body->setUserPointer((void *) room);
    dynamicsWorld->addCollisionObject(body);
    this->transformEntity(room);
    //collisionShapes.push_back(mTriMesh);
}

void CollisionDetector::transformEntity(Entity *entity) {
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
    if (entity->name == "observer") {
        btt.setOrigin(btVector3(c.translation.x, c.translation.y, c.translation.z));
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

void CollisionDetector::addEntity(Entity *entity) {

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
    this->transformEntity(entity);
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