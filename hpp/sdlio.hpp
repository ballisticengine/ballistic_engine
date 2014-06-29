#ifndef SDLIO_HPP
#define	SDLIO_HPP

#include <SDL/SDL.h>
#include "rendererAbstract.hpp"
#include "rendererGL.hpp"

class sdlIO  {
private:
    SDL_Surface *screen;
    videoData vd;
    bool exit;
    rendererGL *renderer;
public:
    void initWindow();
    void eventLoop();
    sdlIO();
    ~sdlIO();
};

#endif 