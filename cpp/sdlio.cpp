#include "sdlio.hpp"
SDL_Window *sdlIO::window=0;
SDL_Renderer *sdlIO::displayRenderer=0;
SDL_Surface *sdlIO::screen=0;

sdlIO::sdlIO() {
   
}

void sdlIO::initWindow() {
   SDL_Init(SDL_INIT_EVERYTHING);
	// SDL_Init(SDL_INIT_VIDEO);
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
   	
	
	while (!engineState::getInstance()->exit()) {
		/*while (SDL_PollEvent(& event)) {
            if (event.type == SDL_QUIT) {
				engineState::getInstance()->setExit(true);
            }
	   }*/
    }
}

 void sdlIO::operator()() {
	 this->eventLoop();
 }

sdlIO::~sdlIO() {
    SDL_Quit();
}