#include "types/texture.hpp"


texture::texture() {
    
}

texture::texture(string filename) {
    this->filename=filename;
}


void texture::free() {
    delete surf;
}

textureFormat texture::getFormat() {
     string ext=Utils::getExt(this->filename);
     if(ext=="bmp") {
     return TF_BGR;
     } else {
         if(this->surf->format->BitsPerPixel==32) {
         return TF_RGBA;
         } else {
             return TF_RGB;
         }
     }
}

void texture::setPixels(void *pixels) {
    this->surf->pixels=pixels;
}

void * texture::getPixels() {
 return surf->pixels;   
}

SDL_Surface * texture::getSurface() {
    return this->surf;
}

void texture::setSurface(SDL_Surface *surf) {
    this->surf=surf;
}

int texture::getWidth() {
    return surf->w;
}

int texture::getHeight() {
    return surf->h;
}

string texture::getFilename() {
	return string(this->filename);
}