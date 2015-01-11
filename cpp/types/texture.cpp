#include "types/texture.hpp"



texture::texture() {
}


void texture::free() {
    delete surf;
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