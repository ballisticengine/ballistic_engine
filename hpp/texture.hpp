/* 
 * File:   texture.hpp
 * Author: maciek
 *
 * Created on June 26, 2014, 6:46 PM
 */

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <SDL/SDL.h>

using namespace std;

class texture {
protected:
    string filename;
    SDL_Surface *surf;
public:
    texture(string fn);
    virtual bool load();
    virtual void free();
    //todo: tać poniższe do renderera
//    virtual void setup()=0;
//    virtual void assign()=0;
    void * getPixels();
    int getWidth();
    int getHeight();
    
};




#endif	/* TEXTURE_HPP */

