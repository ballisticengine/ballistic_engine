#include "resources/loaders/TextureLoader.hpp"


extensions_s TextureLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("gif");
    exts.insert("jpg");
    exts.insert("jpeg");
    exts.insert("png");
    exts.insert("bmp");
    return exts;
}

ResourceType TextureLoader::getType() {
    return TEXTURE;
}

void * TextureLoader::load(string file_name) {

    Texture *tex=new Texture();
    
    SDL_Surface * surf = IMG_Load(file_name.c_str()), *surf2;
    if (!surf) {
        return 0;
    }
    surf2 = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_ABGR8888, 0);

    tex->setSurface(surf2);
    
    return tex;
}

TextureLoader::TextureLoader() {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

TextureLoader::~TextureLoader() {
    IMG_Quit();
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new TextureLoader();
    }
}