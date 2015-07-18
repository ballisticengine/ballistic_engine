#ifndef FACTORY2_HPP
#define	FACTORY2_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "misc/singleton.hpp"
#include "config/path.hpp"
#include "types/Resource.hpp"
#include "libload/LibLoad.hpp"
#include "misc/utils.hpp"
#include "resources/Loader.hpp"

//TODO: resource should contain getRes method which casts it to resource


typedef map<string, void *> factory_items_map;
typedef vector<void *> factory_items_list;

class ResourceManager : public Singleton<ResourceManager> {
protected:
    factory_items_map items;
    factory_items_list item_ptr;
    ResourceManager();
public:
    void * get(string file_name, LoaderType type=NONE);
    ~ResourceManager();

};


#endif	

