#ifndef SDLIO_HPP
#define	SDLIO_HPP


#include <vector>
#include <cstring>
using namespace std;
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
#include "config/EngineState.hpp"
#include "world/World.hpp"
#include "entities/observerEntity.hpp"
#include "config/path.hpp"
#include "io/ttf.hpp"
#include "python/scripting.hpp"
#include "renderer/RenderingManager.hpp"

class SdlIO : public Singleton<SdlIO> {
private:
    static SDL_Surface *screen;
    static SDL_Renderer* displayRenderer;
    static SDL_Window *window;
//    RendererAbstract *r;
    RenderingManager *rendering;
    static SdlIO *me;
    World *w;
    bool fullscreen;
    static int window_w, window_h;
    static void toggleFullscreen();
    size_t anykey(const Uint8 *state, int ksize);
public:
    static void flush();
//    void setRenderer(RendererAbstract *r);
//    RendererAbstract *getRenderer();
    static void initWindow(SdlIO *me);
    void eventLoop();
    void keyboardInputThread();
    void mouseInputThread();
    void inputThread();
    SdlIO();
    ~SdlIO();
};

extern "C" {
void * returnSdlIo();
}

#endif 