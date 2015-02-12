#ifndef SDLIO_HPP
#define	SDLIO_HPP

#ifdef __WIN32__
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif
#include <boost/thread/thread.hpp>
#include "renderer/rendererAbstract.hpp"
#include "renderer/GL/RendererGL.hpp"
#include "misc/singleton.hpp"
#include "config/engineState.hpp"
#include "io/sdlControls.hpp"
#include "world/world.hpp"
#include "entities/observerEntity.hpp"
#include "config/path.hpp"
#include "io/ttf.hpp"
#include "renderer/GL/GLPreview.hpp"

class sdlIO  :  public singleton<sdlIO> {
private:
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
	static SDL_Window *window;
	sdlControls ctrl;
	renderer *r;
        static sdlIO *me;
	world *w;
	bool fullscreen;
        static int window_w,window_h;
        static void toggleFullscreen();
public:
    static void flush();
    void setRenderer(renderer *r);
    renderer *getRenderer();
    static void initWindow(sdlIO *me);
    void eventLoop();
    void previewLoop();
    sdlIO();
    ~sdlIO();
};

#endif 