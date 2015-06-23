/* 
 * File:   loaderMD2.hpp
 * Author: maciek
 *
 * Created on July 20, 2014, 5:45 PM
 */

#ifndef LOADERMD2_HPP
#define	LOADERMD2_HPP

#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "types/types.hpp"
#include "types/shape.hpp"
#include "loaders/md2struct.hpp"
#include "misc/singleton.hpp"
#include "factories/textureFactory.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class LoaderMD2 : public Singleton<LoaderMD2>{
protected:
	void md2ToShape(md2file *md2,Shape *s);
	e_loc scale;
public:
    bool loadMD2(string fn,Shape *s,e_loc scale=1);
};


#endif	/* LOADERMD2_HPP */

