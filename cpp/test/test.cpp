#include <limits.h>
#include <gtest/gtest.h>

#include "types/mathTypes.hpp"
#include "types/plane.hpp"

TEST(Vector3d,Vector3dTest) {
    Vector3d zero=Vector3d();
    Vector3d one=Vector3d(3.14,3.14,3.14);
    ASSERT_DOUBLE_EQ(0,zero.x);
    ASSERT_DOUBLE_EQ(0,zero.y);
    ASSERT_DOUBLE_EQ(0,zero.z);
    ASSERT_DOUBLE_EQ(3.14,one.x);
    ASSERT_DOUBLE_EQ(3.14,one.y);
    ASSERT_DOUBLE_EQ(3.14,one.z);
    Vector3d length=Vector3d(3,2,-1);
    ASSERT_DOUBLE_EQ(3.7416573867739413,length.length());
    Vector3d normal=Vector3d(6,6,6);
    normal=normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(),1);
    normal=Vector3d(1,0,0);
    normal=normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(),1);
   
}

TEST(Plane,PlaneTest) {
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
