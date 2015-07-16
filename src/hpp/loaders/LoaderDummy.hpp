#include "loaders/Loader.hpp"
#ifndef LOADERDUMMY_HPP
#define	LOADERDUMMY_HPP


class LoaderDummy : public Loader {
    public:
        virtual extensions_s getFileExtensions();
};


#endif	/* LOADERDUMMY_HPP */

