#ifndef TEXLOADER_HPP
#define	TEXLOADER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "misc/singleton.hpp"
#include "types/texture.hpp"


class texLoader : public singleton<texLoader> {
    public:
    bool load(string fn,texture *tex);
    texLoader();
    ~texLoader();
};

#endif	

