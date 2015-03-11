#include "io/sdlio.hpp"
SDL_Window *SdlIO::window = 0;
SDL_Renderer *SdlIO::displayRenderer = 0;
SDL_Surface *SdlIO::screen = 0;
SdlIO *SdlIO::me = 0;
int SdlIO::window_w = 0;
int SdlIO::window_h = 0;

SdlIO::SdlIO() {
    w = World::getInstance();

    EngineState::getInstance()->keypress = false;
}

void SdlIO::setRenderer(RendererAbstract *r) {
    this->r = r;
}

RendererAbstract *SdlIO::getRenderer() {
    return this->r;
}

void SdlIO::initWindow(SdlIO *me) {
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_Init(SDL_INIT_VIDEO);
    TTF::getInstance();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(Config::getInstance()->getVD()->width, Config::getInstance()->getVD()->height,
            SDL_WINDOW_OPENGL, &SdlIO::window, &SdlIO::displayRenderer);
    SdlIO::screen = SDL_GetWindowSurface(SdlIO::window);
    SDL_GLContext context;
    SdlIO::me = me;
    context = SDL_GL_CreateContext(window);
    SdlIO::me->window_w = Config::getInstance()->getVD()->width;
    SdlIO::me->window_h = Config::getInstance()->getVD()->height;
    if (EngineState::getInstance()->fullscreen) {
        toggleFullscreen();
    }

}

void SdlIO::flush() {
    SDL_GL_SwapWindow(SdlIO::window);
    //SDL_RenderPresent(displayRenderer);
}

void SdlIO::toggleFullscreen() {
    bool fullscreen = EngineState::getInstance()->fullscreen;
    if (!fullscreen) {
        if (EngineState::getInstance()->desktop_fs) {

            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN);
            int w, h;
            SDL_GetWindowSize(SdlIO::window, &w, &h);
            Config::getInstance()->getVD()->width = w;
            Config::getInstance()->getVD()->height = h;
        } else {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
        }

    } else {
        if (EngineState::getInstance()->desktop_fs) {
            Config::getInstance()->getVD()->width = SdlIO::me->window_w;
            Config::getInstance()->getVD()->height = SdlIO::me->window_h;
        }
        SDL_SetWindowFullscreen(window, 0);
    }



    SdlIO::me->r->setVideoMode();
    EngineState::getInstance()->fullscreen = !fullscreen;
}

void SdlIO::previewLoop() {
    SDL_Event event;
    GLPreview *p;
    while (!EngineState::getInstance()->exit()) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                EngineState::getInstance()->setExit(true);
            }

            if (event.type == SDL_KEYDOWN) {
                p = (GLPreview *) r;
                switch (event.key.keysym.sym) {
                    case SDLK_s:
                        p->c.translation.z--;
                        break;

                    case SDLK_w:
                        p->c.translation.z++;
                        break;

                    case SDLK_LEFT:
                        p->c.rotation.y--;
                        break;

                    case SDLK_RIGHT:
                        p->c.rotation.y++;
                        break;

                    case SDLK_UP:
                        p->c.rotation.z--;
                        break;

                    case SDLK_DOWN:
                        p->c.rotation.z++;
                        break;
                }

            }
        }
        r->render();
    }
}

void SdlIO::eventLoop() {

    SDL_Event event;
    float rot = 0, tr = 0;
    //SDL_EnableKeyRepeat(300, 30);

    boost::thread(boost::ref(this->ctrl));
    Coords vel;
    while (!EngineState::getInstance()->exit()) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                EngineState::getInstance()->setExit(true);
            }

            if (event.type == SDL_KEYDOWN) {
                EngineState::getInstance()->keypress = true;
                ObserverState *observer_state;
                observer_state = this->w->observer.getState();
                observer_state->movement.next_weapon = false;
                observer_state->movement.prev_weapon = false;
                this->w->observer.setState(observer_state);
                this->w->observer.refreshState();

                switch (event.key.keysym.sym) {


                    case SDLK_F1:
                        //wireframes
                        EngineState::getInstance()->debug_visual = !EngineState::getInstance()->debug_visual;
                        break;

                    case SDLK_F2:
                        //ligthing
                        EngineState::getInstance()->lighting = !EngineState::getInstance()->lighting;
                        break;

                    case SDLK_F3:
                        EngineState::getInstance()->noclip = !EngineState::getInstance()->noclip;
                        break;

                    case SDLK_f:
                        toggleFullscreen();

                        break;

                    case SDLK_w:

                        //w->getObserver()->translate(0,-1,0);
                        break;

                    case SDLK_s:


                        vel.translation.y = 1;
                        //w->getObserver()->setVelocity(vel);
                        break;

                    case SDLK_ESCAPE:
                        EngineState::getInstance()->setExit(true);
                        break;
                }

            }

            if (event.type == SDL_KEYUP) {
                EngineState::getInstance()->keypress = false;
                ObserverState *observer_state;
                observer_state = this->w->observer.getState();
                observer_state->movement.next_weapon = false;
                observer_state->movement.prev_weapon = false;
                switch (event.key.keysym.sym) {
                    case SDLK_LEFTBRACKET:
                        //observer_state->movement.next_weapon=false;

                        observer_state->movement.prev_weapon = true;

                        break;

                    case SDLK_RIGHTBRACKET:
                        //observer_state->movement.prev_weapon=false;

                        observer_state->movement.next_weapon = true;

                        break;
                }
                this->w->observer.setState(observer_state);
                this->w->observer.refreshState();
            } else {

            }

        }
        r->render();
    }
}

SdlIO::~SdlIO() {
    SDL_Quit();
}