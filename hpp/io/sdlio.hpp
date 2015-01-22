#ifndef SDLIO_HPP
#define	SDLIO_HPP

#ifdef __WIN32__
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#endif
#include <boost/thread/thread.hpp>
#include "renderer/rendererAbstract.hpp"
#include "renderer/GL/RendererGL.hpp"
#include "misc/singleton.hpp"
#include "config/engineState.hpp"
#include "io/sdlControls.hpp"
#include "world/world.hpp"
#include "config/path.hpp"
#include "io/ttf.hpp"

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