#ifndef TEXLOADER_HPP
#define	TEXLOADER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "resources/Loader.hpp"
#include "types/texture.hpp"


class TextureLoader : public Loader {
    public:
    void * load(string file_name);
    virtual extensions_s getFileExtensions();
    virtual ResourceType getType();
    TextureLoader();
    ~TextureLoader();
};

#endif	

