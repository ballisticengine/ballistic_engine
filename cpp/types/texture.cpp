#include "types/texture.hpp"


texture::texture() {
    
}

texture::texture(string filename) {
    this->filename=filename;
}

texture * texture::clone() {
    texture *clone=new texture();
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    clone->filename=filename;
    
    SDL_Rect rect;
    rect.x=rect.y=0;
    rect.w=this->surf->w;
    rect.h=this->surf->h;
    //clone->surf=SDL_CreateRGBSurface(0,this->surf->w,this->surf->h,32,amask,bmask,gmask,rmask);
    clone->surf=SDL_CreateRGBSurfaceFrom(this->surf->pixels,this->surf->w,this->surf->h,
            32,
            this->surf->pitch,
            amask,bmask,gmask,rmask);
    //SDL_BlitSurface(surf,&rect,clone->surf,&rect);
    return clone;
    
}

void texture::free() {
    delete surf;
}

textureFormat texture::getFormat() {
     string ext=Utils::getExt(this->filename);
     return TF_RGBA;
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