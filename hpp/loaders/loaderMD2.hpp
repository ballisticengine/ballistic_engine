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

class loaderMD2 : public singleton<loaderMD2>{
protected:
	void md2ToShape(md2file *md2,shape *s);
	e_loc scale;
public:
    bool loadMD2(string fn,shape *s,e_loc scale=1);
};


#endif	/* LOADERMD2_HPP */

