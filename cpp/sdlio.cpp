#include "sdlio.hpp"

sdlIO::sdlIO() {
    this->exit = false;
}

void sdlIO::initWindow(videoData vd, renderer *r) {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->screen = SDL_SetVideoMode(vd.width, vd.height, vd.bpp, SDL_OPENGL);
    this->renderer_i = (rendererGL *) r;
    this->renderer_i->init(vd);
    this->renderer_i->setFlush(SDL_GL_SwapBuffers);

}

void sdlIO::eventLoop() {

    SDL_Event event;
    while (!this->exit) {
        while (SDL_PollEvent(& event)) {
            if (event.type == SDL_QUIT) {
                this->exit = true;
            }
            this->renderer_i->render();
        }
    }
}

sdlIO::~sdlIO() {
    SDL_Quit();
}