#ifndef SDLIO_HPP
#define	SDLIO_HPP

#include <SDL/SDL.h>
#include "rendererGL.hpp"

class sdlIO  {
private:
    SDL_Surface *screen;
public:
    void initWindow();
    void eventLoop();
    sdlIO();
    ~sdlIO();
};

#endif 