#include <limits.h>
#include <gtest/gtest.h>

#include "libload/LibLoad.hpp"
#include "resources/Loader.hpp"
#include "resources/ResourceManager.hpp"
#include "world/World.hpp"
#include "world/WorldManager.hpp"

TEST(LibLoad, LibLoadTest) {
    LibLoad *libload = LibLoad::getInstance();
    libload->discoverLoaders();
    Loader *l1 = (Loader *)libload->getLoaderByExtension("txt"),
            *l2 = (Loader *)libload->getLoaderByExtension("noexistent"),
            *l3,
            *l4
            ;
    ASSERT_NE(0, (unsigned long) l1);
    ASSERT_EQ(0, l2);
    l1 = (Loader *)libload->getLoaderByExtension("txt", OTHER);
    l2 = (Loader *)libload->getLoaderByExtension("txt", SHAPE);
    l3 = (Loader *)libload->getLoaderByExtension("nonexistent", OTHER);
    l4 = (Loader *)libload->getLoaderByExtension("nonexistent", SHAPE);
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
          *res4 = rm->get("@table.xml", SHAPE)
            ;
    
    ASSERT_NE(0, (unsigned long) res1);
    ASSERT_NE(0, (unsigned long) res2);
    ASSERT_NE(0, (unsigned long) res3);
    ASSERT_NE(0, (unsigned long) res4);


};

TEST(WorldLoader, WorldLoaderTest) {
    ResourceManager *rm = ResourceManager::getInstance();
    rm->setWD("./data");
    rm->setLevel("level2");
    void *world = rm->get("level.xml", LEVEL);
    ASSERT_NE(0, (unsigned long) world);
    WorldManager::getInstance()->setWorld((World *)world);
    WorldManager::getInstance()->saveInto("./data/test/levels/save_level/test.xml");
    rm->setWD("./data/test");
    rm->setLevel("save_level");
    void *world_saved = rm->get("test.xml", LEVEL);
};

