#include "texture.hpp"

texture::texture(string fn) {
    this->filename=fn;
}

bool texture::load() {
   surf=SDL_LoadBMP(this->filename.c_str());
   if(!surf) {
       return false;
   }
   return true;
}

void texture::free() {

}
