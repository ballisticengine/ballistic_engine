#ifndef FACTORY2_HPP
#define	FACTORY2_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
using namespace std;
#include "misc/singleton.hpp"
#include "config/path.hpp"
#include "types/Resource.hpp"
#include "libload/LibLoad.hpp"
#include "misc/utils.hpp"
#include "resources/Loader.hpp"

//TODO: resource should contain getRes method which casts it to resource


typedef map<string, void *> factory_items_map;
typedef vector<void *> factory_items_vector;

class ResourceManager : public Singleton<ResourceManager> {
protected:
    FRIEND_TEST(ResourceManager, ResourceManagerTest);
    string wd, lvl;
    factory_items_map items;
    factory_items_vector items_v;
    virtual string getSubDir(LoaderType type);
    virtual string resolveFilename(string file_name, LoaderType type);
public:
    void * get(string file_name, LoaderType type = NONE);
    virtual void setWD(string wd);
    virtual string getWD();
    virtual void setLevel(string lvl);
    virtual string getLevel();
    factory_items_vector getAll();

    ResourceManager();
    ~ResourceManager();

};


#endif	

