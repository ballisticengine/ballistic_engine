#ifndef SQUARE_WORLD_LOADER_HPP
#define	SQUARE_WORLD_LOADER_HPP

#include "resources/Loader.hpp"


class SquareLoader : public Loader {
    public:
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
        virtual ResourceType getType();
};

#endif