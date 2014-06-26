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
public:
    texture(string fn);
    bool load();
    void free();
    
};

class textureFactory {
   vector<texture *>  textures; 
   
};



#endif	/* TEXTURE_HPP */

