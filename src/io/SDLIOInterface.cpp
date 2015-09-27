#include "SDLIOInterface.hpp"

SDL_Window *SDLIOInterface::window = 0;
SDL_Renderer *SDLIOInterface::displayRenderer = 0;
SDLIOInterface *SDLIOInterface::me = 0;

void SDLIOInterface::init(SDLIOInterface *me) {
     SDLIOInterface::me = me;
     me->initWindow();
}

void SDLIOInterface::flush() {
    SDL_GL_SwapWindow(SDLIOInterface::window);
}

SDL_Renderer * SDLIOInterface::getSDLRenderer() {
     return SDLIOInterface::displayRenderer;
}

SDL_Window * SDLIOInterface::getSDLWindow() {
     return SDLIOInterface::window;
}
