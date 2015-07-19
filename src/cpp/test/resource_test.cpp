#include <limits.h>
#include <gtest/gtest.h>

#include "libload/LibLoad.hpp"
#include "resources/Loader.hpp"
#include "resources/ResourceManager.hpp"

TEST(LibLoad, LibLoadTest) {
    LibLoad *libload = LibLoad::getInstance();
    libload->discoverLoaders();
    Loader *l1 = libload->getLoaderByExtension("txt"),
            *l2 = libload->getLoaderByExtension("noexistent"),
            *l3,
            *l4
            ;
    ASSERT_NE(0, (unsigned long) l1);
    ASSERT_EQ(0, l2);
    l1 = libload->getLoaderByExtension("txt", OTHER);
    l2 = libload->getLoaderByExtension("txt", SHAPE);
    l3 = libload->getLoaderByExtension("nonexistent", OTHER);
    l4 = libload->getLoaderByExtension("nonexistent", SHAPE);
    ASSERT_NE(0, (unsigned long) l1);
    ASSERT_EQ(0, l2);
    ASSERT_EQ(0, l3);
    ASSERT_EQ(0, l4);

};

TEST(ResourceManager, ResourceManagerTest) {
    ResourceManager *rm = ResourceManager::getInstance();

    rm->setWD("./data/test");
    rm->setLevel("test_level");
    void *res1 = rm->get("@test.txt"),
          *res2 = rm->get("@w_machinegun.md2"),
          *res3 = rm->get("@car.bmp"),
          *res4 = rm->get("@table.xml")
            ;
    
    ASSERT_NE(0, (unsigned long) res1);
    ASSERT_NE(0, (unsigned long) res2);
    ASSERT_NE(0, (unsigned long) res3);
    ASSERT_NE(0, (unsigned long) res4);


};