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




struct LoadedResource {
    void *object;
    ResourceType type;
    
};

typedef map<string, LoadedResource *> factory_items_map;
typedef vector<LoadedResource *> factory_items_vector;
typedef map<void *, Resource *> res_obj;


class ResourceManager : public Singleton<ResourceManager> {
protected:
    FRIEND_TEST(ResourceManager, ResourceManagerTest);
    string wd, lvl;
    factory_items_map items;
    factory_items_vector items_v;
    res_obj resmap;
    virtual string getSubDir(ResourceType type);
    virtual string resolveFilename(string file_name, ResourceType type);
public:
    void * get(string file_name, ResourceType type = NONE);
    virtual void setWD(string wd);
    virtual string getWD();
    virtual void setLevel(string lvl);
    virtual string getLevel();
    virtual factory_items_vector getByType(ResourceType type);
    virtual void resolveDependencies(Loader *loader);
    virtual void resolveAllDependencies();
    virtual Resource * getResource(void *object);
    ResourceManager();
    ~ResourceManager(); //TODO: proper cleanup

};


#endif	

