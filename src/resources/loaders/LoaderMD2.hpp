#ifndef LOADERMD22_HPP
#define	LOADERMD22_HPP

#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "types/types.hpp"
#include "types/shape.hpp"
#include "resources/loaders/md2struct.hpp"
#include "resources/Loader.hpp"
#include "misc/singleton.hpp"

class LoaderMD2 : public Loader{
protected:
	void md2ToShape(md2file *md2,Shape *s);
	e_loc scale;
public:
    virtual extensions_s getFileExtensions();
    virtual ResourceType getType();
    virtual void *load(string file_name);
};


#endif	/* LOADERMD2_HPP */

