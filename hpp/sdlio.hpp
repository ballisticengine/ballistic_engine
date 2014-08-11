#ifndef SDLIO_HPP
#define	SDLIO_HPP

#include <SDL/SDL.h>
#include <boost/thread/thread.hpp>
#include "rendererAbstract.hpp"
#include "rendererGL.hpp"
#include "singleton.hpp"
#include "engineState.hpp"
#include "sdlControls.hpp"

class sdlIO  :  public singleton<sdlIO> {
private:
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
	static SDL_Window *window;
	sdlControls ctrl;
	renderer *r;
public:
    static void flush();
    void setRenderer(renderer *r);
	static void initWindow();
    void eventLoop();
    sdlIO();
    ~sdlIO();
};

#endif 