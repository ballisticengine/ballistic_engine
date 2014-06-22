#include "sdlio.hpp"

sdlIO::sdlIO() {
    this->exit=false;
}

void sdlIO::initWindow() {
   SDL_Init( SDL_INIT_EVERYTHING );
   
   vd.width=640;
   vd.height=480;
   vd.bpp=32;
   this->screen=SDL_SetVideoMode( vd.width, vd.height, vd.bpp, SDL_OPENGL);
   this->renderer=new rendererGL();
   this->renderer->init(vd);
   
}

void sdlIO::eventLoop() {
    SDL_Event event;
    while( !this->exit )
    {
        while( SDL_PollEvent( & event ) )
        {
            if( event.type == SDL_QUIT )
            {
                this->exit = true;
            }
        }
    }
} 

sdlIO::~sdlIO() {
    SDL_Quit();
}