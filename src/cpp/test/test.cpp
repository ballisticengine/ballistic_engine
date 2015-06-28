#include <limits.h>
#include <gtest/gtest.h>


#include "types/mathTypes.hpp"
#include "types/plane.hpp"
#include "types/shape.hpp"
#include "types/boundingCube.hpp"
#include "entities/entity.hpp"
#include "entities/observerEntity.hpp"
#include "entities/ObjectEntity.hpp"
#include "physics/collisionDetector.hpp"

TEST(Vector3d, Vector3dTest) {
    Vector3d zero = Vector3d();
    Vector3d one = Vector3d(3.14, 3.14, 3.14);
    ASSERT_DOUBLE_EQ(0, zero.x);
    ASSERT_DOUBLE_EQ(0, zero.y);
    ASSERT_DOUBLE_EQ(0, zero.z);
    ASSERT_DOUBLE_EQ(3.14, one.x);
    ASSERT_DOUBLE_EQ(3.14, one.y);
    ASSERT_DOUBLE_EQ(3.14, one.z);
    Vector3d length = Vector3d(3, 2, -1);
    ASSERT_DOUBLE_EQ(3.7416573867739413, length.length());
    Vector3d normal = Vector3d(6, 6, 6);
    normal = normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(), 1);
    normal = Vector3d(1, 0, 0);
    normal = normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(), 1);

}

TEST(CollisionDetector, CollisionDetectorTest) {
    CollisionDetector collisions;
    ObjectEntity *e1 = new ObjectEntity();        
    ObserverEntity *e2 = new ObserverEntity();

    Coords c;
    
    BoundingCube *bounding1 = new BoundingCube(0, 0, 0, 10, 10, 10),
            *bounding2 = new BoundingCube(0, 0, 0, 10, 10, 10);
    e1->name = "Entity1";
    e2->name = "Observer";
    e1->addBoundingBox(bounding1);
  
    e1->locate(0,0,0);
    e2->locate(0,0,0);
    
    collisions.addEntity((Entity *) e1);
    collisions.addEntity((Entity *) e2);
    //collisions.step(1);
    //e2->translate(-100,0,0);
    collisions.objectsCollide(e1,e2,c);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
