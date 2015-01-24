#include "io/sdlio.hpp"
SDL_Window *sdlIO::window = 0;
SDL_Renderer *sdlIO::displayRenderer = 0;
SDL_Surface *sdlIO::screen = 0;

sdlIO::sdlIO() {
    w = world::getInstance();
    fullscreen = false;
    engineState::getInstance()->keypress = false;
}

void sdlIO::setRenderer(renderer *r) {
    this->r = r;
}

void sdlIO::initWindow() {
    //SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_VIDEO);
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
    context = SDL_GL_CreateContext(window);

}

void sdlIO::flush() {
    SDL_GL_SwapWindow(sdlIO::window);
    //SDL_RenderPresent(displayRenderer);
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
                        if (!fullscreen) {
                            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                        } else {
                            SDL_SetWindowFullscreen(window, 0);
                        }
                        fullscreen = !fullscreen;
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