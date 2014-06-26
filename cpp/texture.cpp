#include "texture.hpp"

texture::texture(string fn) {
    this->filename=fn;
}

bool texture::load() {
   SDL_LoadBMP(this->filename.c_str());
}

void texture::free() {

}
