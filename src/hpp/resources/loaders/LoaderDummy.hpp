
#ifndef LOADERDUMMY_HPP
#define	LOADERDUMMY_HPP

#include <cstdio>
#include <cstdlib>

using namespace std;

#include "resources/Loader.hpp"

class LoaderDummy : public Loader {
    public:
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
        ResourceType getType();
};



#endif	/* LOADERDUMMY_HPP */

