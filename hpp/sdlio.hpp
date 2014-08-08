#ifndef SDLIO_HPP
#define	SDLIO_HPP

#include <SDL/SDL.h>
#include "rendererAbstract.hpp"
#include "rendererGL.hpp"
#include "singleton.hpp"
#include "engineState.hpp"

class sdlIO  :  public singleton<sdlIO> {
private:
    SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
	static SDL_Window *window;
    videoData vd;
    bool exit;
    rendererGL *renderer_i;
public:
    static void flush();
    void initWindow();
    void operator()();
	void eventLoop();
    sdlIO();
    ~sdlIO();
};

#endif 