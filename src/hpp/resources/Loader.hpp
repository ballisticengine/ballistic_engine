#ifndef LOADER_HPP
#define	LOADER_HPP

#include <string>
#include <set>

using namespace std;


enum LoaderType {
    LEVEL,
    TEXTURE,
    SHAPE,
    OTHER,
    NONE
};

typedef set<string> extensions_s;

class Loader {
public:
    virtual extensions_s getFileExtensions()=0;
    virtual LoaderType getType()=0;
    virtual void *load(string file_name)=0;
    virtual bool handlesEntension(string extension);
};

#endif	

