#include "sdlio.hpp"
SDL_Window *sdlIO::window=0;
SDL_Renderer *sdlIO::displayRenderer=0;
SDL_Surface *sdlIO::screen=0;

sdlIO::sdlIO() {
	w=world::getInstance();
}

void sdlIO::setRenderer(renderer *r) {
 this->r=r;
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
   	
	boost::thread(boost::ref(this->ctrl));
	TrRot vel;
	while (!engineState::getInstance()->exit()) {
		while (SDL_PollEvent(& event)) {
            if (event.type == SDL_QUIT) {
				engineState::getInstance()->setExit(true);
            }
			if (event.type==SDL_KEYDOWN) {
				 switch (event.key.keysym.sym) {
					case SDLK_F1:
						//wireframes
						engineState::getInstance()->debug_visual=!engineState::getInstance()->debug_visual;
						break;
				 
					case SDLK_F2:
						//ligthing
						engineState::getInstance()->lighting=!engineState::getInstance()->lighting;
						break;
					
					case SDLK_F3:
						engineState::getInstance()->noclip=!engineState::getInstance()->noclip;
						break;

					case SDLK_f:
						//fullscreen
						break;
					
					case SDLK_w:
						
						//w->getObserver()->translate(0,-1,0);
						break;

					case SDLK_s:
						
						
						vel.t.y=1;
						//w->getObserver()->setVelocity(vel);
						break;

					case SDLK_ESCAPE:
						engineState::getInstance()->setExit(true);
						break;
				 }
			}

	   }
		r->render();
    }
}



sdlIO::~sdlIO() {
    SDL_Quit();
}