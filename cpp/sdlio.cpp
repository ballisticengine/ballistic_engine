#include "sdlio.hpp"
SDL_Window *sdlIO::window=0;
SDL_Renderer *sdlIO::displayRenderer=0;

sdlIO::sdlIO() {
    this->exit = false;
}

void sdlIO::initWindow(videoData vd, renderer *r) {
   // SDL_Init(SDL_INIT_EVERYTHING);
	 SDL_Init(SDL_INIT_VIDEO);
	 SDL_CreateWindowAndRenderer(vd.width, vd.height, SDL_WINDOW_OPENGL, &sdlIO::window, &sdlIO::displayRenderer);
    this->screen = SDL_GetWindowSurface(sdlIO::window);
	SDL_GLContext context;
	context = SDL_GL_CreateContext(window);
	
	renderer_i=(rendererGL*)r;
}

void sdlIO::flush() {
 SDL_GL_SwapWindow(sdlIO::window); 
 //SDL_RenderPresent(displayRenderer);
}

void sdlIO::eventLoop() {

    SDL_Event event;
    float rot = 0, tr = 0;
    //SDL_EnableKeyRepeat(300, 30);
   	boost::thread rt(boost::ref(*renderer_i));
	
	while (!this->exit) {

		
    /*    while (SDL_PollEvent(& event)) {
            if (event.type == SDL_QUIT) {
                this->exit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    rot++;
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    rot--;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    tr += 1;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    tr -= 1;
                }
              
            }
			
        }*/
		//renderer_i->render();
    }
}

 void sdlIO::operator()() {
  while(1) {
  }
 }

sdlIO::~sdlIO() {
    SDL_Quit();
}