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

#include "types.hpp"
#include "md2struct.hpp"
#include "singleton.hpp"

class loaderMD2 : public singleton<loaderMD2>{
protected:
	void md2ToShape(md2file *md2,shape *s);
	
public:
    bool loadMD2(string fn,shape *s);
};


#endif	/* LOADERMD2_HPP */

