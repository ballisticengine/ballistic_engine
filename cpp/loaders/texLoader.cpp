#include "loaders/texLoader.hpp"


 bool TexLoader::load(string fn,Texture *tex) {
    
    SDL_Surface * surf = IMG_Load(fn.c_str()),*surf2;
    surf2= SDL_ConvertSurfaceFormat(surf,SDL_PIXELFORMAT_ABGR8888,0);
    if (!surf) {
        return false;
    }
    tex->setSurface(surf2);
    return true;
 }

 TexLoader::TexLoader() {
     IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
 }
 
 TexLoader::~TexLoader() {
     IMG_Quit();
 }