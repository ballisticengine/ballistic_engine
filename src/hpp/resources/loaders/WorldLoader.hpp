#ifndef WORLDLOADER_HPP
#define	WORLDLOADER_HPP

#include "resources/Loader.hpp"

//include world here and then return world from that class, ie. in enginge.cpp

class WorldLoader : public Loader {
    public:
        virtual extensions_s getFileExtensions();
        virtual ResourceType getType();
        virtual void *load(string file_name);
};

#endif	

