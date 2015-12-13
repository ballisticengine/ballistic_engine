#ifndef XMLWORLDLOADER_HPP
#define	XMLWORLDLOADER_HPP

#include "resources/WorldLoader.hpp"


//include world here and then return world from that class, ie. in enginge.cpp

class XMLWorldLoader : public WorldLoader {
    public:
        XMLWorldLoader();
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
        virtual bool save(World *world, string file_name);

};

#endif	

