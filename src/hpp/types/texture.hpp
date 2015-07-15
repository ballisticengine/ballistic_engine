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
#ifdef __WIN32__
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

using namespace std;

#include "misc/utils.hpp"

enum textureFormat {
    TF_RGBA,
    TF_RGB,
    TF_BGR,
};

class Texture {
protected:
    string filename, orig_filename;
   
public:
     SDL_Surface *surf;
    Texture();
    Texture(string filename, string orig_filename);
    Texture *clone();
    virtual textureFormat getFormat();
   virtual void free();
    
    SDL_Surface *getSurface();
    void setSurface(SDL_Surface *surf);
    
    virtual void * getPixels();
    virtual void setPixels(void *pixels);
    
    virtual int getWidth();
    virtual int getHeight();
    virtual string getFilename();
    virtual string getOrigFilename();
    
    
};




#endif	/* TEXTURE_HPP */

