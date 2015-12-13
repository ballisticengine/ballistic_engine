#ifndef SQUARE_WORLD_LOADER_HPP
#define	SQUARE_WORLD_LOADER_HPP

#include "resources/Loader.hpp"


//include world here and then return world from that class, ie. in enginge.cpp

class SquareLoader : public Loader {
    public:
        SquareLoader();
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
         virtual ResourceType getType();
};

#endif