#include "loaders/Loader.hpp"
#ifndef LOADERDUMMY_HPP
#define	LOADERDUMMY_HPP


class LoaderDummy : public Loader {
    public:
        virtual extensions_s getFileExtensions();
        virtual void *load(string file_name);
        LoaderType getType();
};



#endif	/* LOADERDUMMY_HPP */

