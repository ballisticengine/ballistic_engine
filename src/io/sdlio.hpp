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
#include "misc/singleton.hpp"
#include "config/EngineState.hpp"
#include "world/World.hpp"
#include "entities/observerEntity.hpp"
#include "config/path.hpp"
#include "config/Config.hpp"
#include "io/ttf.hpp"
#include "python/scripting.hpp"
#include "renderer/RenderingManager.hpp"
#include "ui/ui.hpp"
#include "io/SDLIOInterface.hpp"

class SdlIO : public SDLIOInterface, public Singleton<SdlIO> {
private:
    RenderingManager *rendering;
    World *w;
    bool fullscreen;
    static int window_w, window_h;
    static void toggleFullscreen();
    size_t anykey(const Uint8 *state, int ksize);
    KeyBindings *key_bindings;
    void initWindow();
public:
    void eventLoop();
    void keyboardInputThread();
    void mouseInputThread();
    void inputThread();
    void attachMouse(bool attach=true);
    SdlIO();
    ~SdlIO();
};

extern "C" {
void * returnSdlIo();
}

#endif 