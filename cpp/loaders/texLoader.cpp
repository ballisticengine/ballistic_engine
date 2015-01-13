#include "loaders/texLoader.hpp"


 bool texLoader::load(string fn,texture *tex) {
    
    SDL_Surface * surf = IMG_Load(fn.c_str()),*surf2;
    surf2= SDL_ConvertSurfaceFormat(surf,SDL_PIXELFORMAT_ABGR8888,0);
    if (!surf) {
        return false;
    }
    tex->setSurface(surf2);
    return true;
 }

 texLoader::texLoader() {
     IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
 }
 
 texLoader::~texLoader() {
     IMG_Quit();
 }