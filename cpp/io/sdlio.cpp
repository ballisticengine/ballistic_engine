#include "io/sdlio.hpp"
SDL_Window *sdlIO::window = 0;
SDL_Renderer *sdlIO::displayRenderer = 0;
SDL_Surface *sdlIO::screen = 0;
sdlIO *sdlIO::me = 0;
int sdlIO::window_w = 0;
int sdlIO::window_h = 0;

sdlIO::sdlIO() {
    w = world::getInstance();

    engineState::getInstance()->keypress = false;
}

void sdlIO::setRenderer(renderer *r) {
    this->r = r;
}

renderer *sdlIO::getRenderer() {
    return this->r;
}

void sdlIO::initWindow(sdlIO *me) {
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

    SDL_CreateWindowAndRenderer(config::getInstance()->getVD()->width, config::getInstance()->getVD()->height,
            SDL_WINDOW_OPENGL, &sdlIO::window, &sdlIO::displayRenderer);
    sdlIO::screen = SDL_GetWindowSurface(sdlIO::window);
    SDL_GLContext context;
    sdlIO::me = me;
    context = SDL_GL_CreateContext(window);
    sdlIO::me->window_w = config::getInstance()->getVD()->width;
    sdlIO::me->window_h = config::getInstance()->getVD()->height;
    if (engineState::getInstance()->fullscreen) {
        toggleFullscreen();
    }

}

void sdlIO::flush() {
    SDL_GL_SwapWindow(sdlIO::window);
    //SDL_RenderPresent(displayRenderer);
}

void sdlIO::toggleFullscreen() {
    bool fullscreen = engineState::getInstance()->fullscreen;
    if (!fullscreen) {
        if (engineState::getInstance()->desktop_fs) {

            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN);
            int w, h;
            SDL_GetWindowSize(sdlIO::window, &w, &h);
            config::getInstance()->getVD()->width = w;
            config::getInstance()->getVD()->height = h;
        } else {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
        }

    } else {
        if (engineState::getInstance()->desktop_fs) {
            config::getInstance()->getVD()->width = sdlIO::me->window_w;
            config::getInstance()->getVD()->height = sdlIO::me->window_h;
        }
        SDL_SetWindowFullscreen(window, 0);
    }



    sdlIO::me->r->setVideoMode();
    engineState::getInstance()->fullscreen = !fullscreen;
}

void sdlIO::previewLoop() {
    SDL_Event event;
    GLPreview *p;
    while (!engineState::getInstance()->exit()) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                engineState::getInstance()->setExit(true);
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

void sdlIO::eventLoop() {

    SDL_Event event;
    float rot = 0, tr = 0;
    //SDL_EnableKeyRepeat(300, 30);

    boost::thread(boost::ref(this->ctrl));
    TrRot vel;
    while (!engineState::getInstance()->exit()) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                engineState::getInstance()->setExit(true);
            }

            if (event.type == SDL_KEYDOWN) {
                engineState::getInstance()->keypress = true;
                ObserverState *observer_state;
                observer_state = this->w->observer.getState();
                observer_state->movement.next_weapon = false;
                observer_state->movement.prev_weapon = false;
                this->w->observer.setState(observer_state);
                this->w->observer.refreshState();

                switch (event.key.keysym.sym) {


                    case SDLK_F1:
                        //wireframes
                        engineState::getInstance()->debug_visual = !engineState::getInstance()->debug_visual;
                        break;

                    case SDLK_F2:
                        //ligthing
                        engineState::getInstance()->lighting = !engineState::getInstance()->lighting;
                        break;

                    case SDLK_F3:
                        engineState::getInstance()->noclip = !engineState::getInstance()->noclip;
                        break;

                    case SDLK_f:
                        toggleFullscreen();

                        break;

                    case SDLK_w:

                        //w->getObserver()->translate(0,-1,0);
                        break;

                    case SDLK_s:


                        vel.t.y = 1;
                        //w->getObserver()->setVelocity(vel);
                        break;

                    case SDLK_ESCAPE:
                        engineState::getInstance()->setExit(true);
                        break;
                }

            }

            if (event.type == SDL_KEYUP) {
                engineState::getInstance()->keypress = false;
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

sdlIO::~sdlIO() {
    SDL_Quit();
}