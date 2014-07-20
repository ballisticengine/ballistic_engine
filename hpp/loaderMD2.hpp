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

using namespace std;

#include "types.hpp"
#include "md2struct.hpp"


class loaderMD2 {
   
public:
    bool loadMD2(string fn,shape *s);
};


#endif	/* LOADERMD2_HPP */

