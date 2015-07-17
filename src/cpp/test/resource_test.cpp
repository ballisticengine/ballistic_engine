#include <limits.h>
#include <gtest/gtest.h>

#include "libload/LibLoad.hpp"
#include "loaders/dynamic/Loader.hpp"
#include "factories/factory.hpp"

TEST(LibLoad, LibLoadTest) {
    LibLoad *libload = LibLoad::getInstance();
    libload->discoverLoaders();
    Loader *l1=libload->getLoaderByExtension("txt"), 
           *l2=libload->getLoaderByExtension("noexistent")
            ;
    ASSERT_NE(0, (unsigned long)l1);
    ASSERT_EQ(0, l2);
    
};

TEST(Factory, FactoryTest) {
    
};