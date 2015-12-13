#ifndef SQUARE_WORLD_LOADER_HPP
#define	SQUARE_WORLD_LOADER_HPP

#include "resources/WorldLoader.hpp"


//include world here and then return world from that class, ie. in enginge.cpp

class SquareWorldLoader : public WorldLoader {
    public:
        SquareWorldLoader();
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
        virtual bool save(World *world, string file_name);
};

#endif