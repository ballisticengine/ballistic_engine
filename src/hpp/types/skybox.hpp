
#ifndef SKYBOX_HPP
#define	SKYBOX_HPP

#include <string>
#include <iostream>

using namespace std;

#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"



class Skybox {
    Ballistic::Types::Texture *sky;
    Shape *box;
   
public:
    Skybox(string tex_name);
    Skybox(Ballistic::Types::Texture *tex);
    Shape *getShape();
    Ballistic::Types::Texture *getTexture();
     void makeShape(float x,float y);
};


#endif	/* SKYBOX_HPP */

