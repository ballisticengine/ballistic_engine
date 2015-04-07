#include <limits.h>
#include <gtest/gtest.h>

#include "types/mathTypes.hpp"

TEST(Vector3d,VectorTest) {
    Vector3d zero=Vector3d();
    Vector3d one=Vector3d(3.14,3.14,3.14);
    ASSERT_DOUBLE_EQ(0,zero.x);
    ASSERT_DOUBLE_EQ(0,zero.y);
    ASSERT_DOUBLE_EQ(0,zero.z);
    ASSERT_DOUBLE_EQ(3.14,one.x);
    ASSERT_DOUBLE_EQ(3.14,one.y);
    ASSERT_DOUBLE_EQ(3.14,one.z);
    
    
    Vector3d length=Vector3d(1,1,1);
    //EXPECT_TRUE(!length==1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
