#ifndef SDLIOINTERFACE_HPP
#define	SDLIOINTERFACE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "renderer/RenderingManager.hpp"

class SDLIOInterface {
protected:
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
    static SDL_Window *window;
    RenderingManager *rendering;
    static SDLIOInterface *me;
    
    virtual void initWindow()=0;
public:
    static void init(SDLIOInterface *me);
    static void flush();
    virtual void eventLoop()=0;
    virtual SDL_Renderer * getSDLRenderer();
    virtual SDL_Window * getSDLWindow();
};

#endif	

