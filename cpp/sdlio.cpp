#include "sdlio.hpp"

sdlIO::sdlIO() {
    
}

void sdlIO::initWindow() {
   SDL_Init( SDL_INIT_EVERYTHING );
   this->screen=SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
   rendererGL *r=(rendererGL *)rendererGL::getInstance();
}

void sdlIO::eventLoop() {
    SDL_Delay(1000);
} 

sdlIO::~sdlIO() {
    SDL_Quit();
}