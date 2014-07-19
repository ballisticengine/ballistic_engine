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
    float rot=0,tr=0;
    SDL_EnableKeyRepeat(300, 30) ;
    while (!this->exit) {
        
        
        while (SDL_PollEvent(& event)) {
            if (event.type == SDL_QUIT) {
                this->exit = true;
            }
            if(event.type==SDL_KEYDOWN)  {
                if(event.key.keysym.sym==SDLK_LEFT) {
                     rot++;
                } 
                if(event.key.keysym.sym==SDLK_RIGHT) {
                    rot--;
                }
                if(event.key.keysym.sym==SDLK_UP) {
                 tr+=0.1;   
                }
                if(event.key.keysym.sym==SDLK_DOWN) {
                    tr-=0.1;
                }
                this->renderer_i->rotate(rot);
                this->renderer_i->translate(0,0,tr);
            }
            
            
            this->renderer_i->render();
        }
    }
}

sdlIO::~sdlIO() {
    SDL_Quit();
}