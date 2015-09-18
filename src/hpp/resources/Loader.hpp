#ifndef LOADER_HPP
#define	LOADER_HPP

#include <string>
#include <set>
#include <vector>

using namespace std;


#include "resources/exceptions.hpp"
#include "types/Resource.hpp"


enum ResourceType {
    LEVEL,
    TEXTURE,
    SHAPE,
    OTHER,
    NONE
};

struct LoaderDependency {
    string file_name;
    void **target;
};

typedef vector<LoaderDependency> dep_list; 
typedef set<string> extensions_s;

class Loader {
protected:
    dep_list dependencies;
    virtual void addDependency(string file_name, void **target);
public:
    virtual extensions_s getFileExtensions()=0;
    virtual ResourceType getType()=0;
    virtual size_t getPriority();
    virtual void *load(string file_name)=0;
    virtual void *loadFromData(void *data, size_t size);
    virtual bool handlesEntension(string extension);
    virtual dep_list getDependencies();
    virtual void cleanDependencies();
};

#endif	

