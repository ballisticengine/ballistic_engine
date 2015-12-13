#ifndef WORLDLOADER_HPP
#define	WORLDLOADER_HPP

#include "resources/Loader.hpp"
#include "world/World.hpp"

class WorldLoader : public Loader {
public:
    virtual ResourceType getType();
    virtual extensions_s getFileExtensions();
    virtual bool save(World *world, string level_filename, string geometry_filename);
};


#endif	

