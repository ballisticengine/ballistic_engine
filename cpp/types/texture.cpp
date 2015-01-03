#include "types/texture.hpp"

texture::texture(string fn) {
    this->filename = fn;
}

texture::texture() {
}

bool texture::load() {
    cout << this->filename << endl;
    cout.flush();
    surf = SDL_LoadBMP(this->filename.c_str());
    if (!surf) {
        return false;
    }
    return true;
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