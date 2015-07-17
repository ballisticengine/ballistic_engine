#include "loaders/dynamic/Loader.hpp"
#ifndef LOADERDUMMY_HPP
#define	LOADERDUMMY_HPP


class LoaderDummy : public Loader {
    public:
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
};



#endif	/* LOADERDUMMY_HPP */

