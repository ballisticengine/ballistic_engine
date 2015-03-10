#ifndef TEXLOADER_HPP
#define	TEXLOADER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "misc/singleton.hpp"
#include "types/texture.hpp"


class TexLoader : public Singleton<TexLoader> {
    public:
    bool load(string fn,Texture *tex);
    TexLoader();
    ~TexLoader();
};

#endif	

