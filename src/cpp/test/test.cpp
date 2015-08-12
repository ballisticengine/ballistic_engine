#include <limits.h>
#include <gtest/gtest.h>


#include "physics_test.cpp"
#include "resource_test.cpp"
#include "renderer_interfaces_test.cpp"
#include "config_test.cpp"
#include "scripting_test.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
