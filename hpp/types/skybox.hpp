
#ifndef SKYBOX_HPP
#define	SKYBOX_HPP

#include <string>
#include <iostream>

using namespace std;

#include "types/types.hpp"
#include "types/texture.hpp"


class skybox {
    texture *sky;
    shape *box;
   
public:
    skybox(string tex_name);
    skybox(texture *tex);
    shape *getShape();
    texture *getTexture();
     void makeShape(float x,float y);
};


#endif	/* SKYBOX_HPP */

