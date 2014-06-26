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
    virtual void setup()=0;
    virtual void assign()=0;
    Uint8 * getPixels();
    
};

class textureFactory {
   vector<texture *>  textures; 
   
};



#endif	/* TEXTURE_HPP */

