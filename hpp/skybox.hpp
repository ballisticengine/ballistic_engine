
#ifndef SKYBOX_HPP
#define	SKYBOX_HPP

#include <string>
#include <iostream>

using namespace std;

#include "types.hpp"
#include "texture.hpp"


class skybox {
    texture *sky;
    shape *box;
    void makeShape();
public:
    skybox(string tex_name);
    skybox(texture *tex);
};


#endif	/* SKYBOX_HPP */

