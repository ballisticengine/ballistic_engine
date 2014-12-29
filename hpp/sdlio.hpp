#ifndef SDLIO_HPP
#define	SDLIO_HPP

#ifdef __WIN32__
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <boost/thread/thread.hpp>
#include "rendererAbstract.hpp"
#include "RendererGL.hpp"
#include "singleton.hpp"
#include "engineState.hpp"
#include "sdlControls.hpp"
#include "world.hpp"

class sdlIO  :  public singleton<sdlIO> {
private:
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
	static SDL_Window *window;
	sdlControls ctrl;
	renderer *r;
	world *w;
	bool fullscreen;
public:
    static void flush();
    void setRenderer(renderer *r);
	static void initWindow();
    void eventLoop();
    sdlIO();
    ~sdlIO();
};

#endif 