#ifndef WORLDLOADER_HPP
#define	WORLDLOADER_HPP

#include "resources/Loader.hpp"

class WorldLoader : public Loader {
public:
    virtual ResourceType getType();
    virtual extensions_s getFileExtensions();
};


#endif	

