#include "sdlio.hpp"
SDL_Window *sdlIO::window=0;
SDL_Renderer *sdlIO::displayRenderer=0;
SDL_Surface *sdlIO::screen=0;

sdlIO::sdlIO() {
   
}

<<<<<<< HEAD
void sdlIO::initWindow() {
   SDL_Init(SDL_INIT_EVERYTHING);
	// SDL_Init(SDL_INIT_VIDEO);
	 SDL_CreateWindowAndRenderer(config::getInstance()->getVD()->width, config::getInstance()->getVD()->height, 
		 SDL_WINDOW_OPENGL, &sdlIO::window, &sdlIO::displayRenderer);
    sdlIO::screen = SDL_GetWindowSurface(sdlIO::window);
	SDL_GLContext context;
	context = SDL_GL_CreateContext(window);
=======
void sdlIO::initWindow(videoData vd, renderer *r) {
   // SDL_Init(SDL_INIT_EVERYTHING);
	 SDL_Init(SDL_INIT_VIDEO);
	 SDL_CreateWindowAndRenderer(config::getInstance()->getVD()->width, config::getInstance()->getVD()->height, SDL_WINDOW_OPENGL, &sdlIO::window, &sdlIO::displayRenderer);
	/*sdlIO::window = SDL_CreateWindow("My Game Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
			vd.width, vd.height,
            SDL_WINDOW_OPENGL);*/
    this->screen = SDL_GetWindowSurface(sdlIO::window);
	SDL_GLContext context;
context = SDL_GL_CreateContext(window);
    this->renderer_i = (rendererGL *) r;
    this->renderer_i->init(vd);
    this->renderer_i->setFlush(sdlIO::flush);

<<<<<<< HEAD
>>>>>>> parent of 5385397... before refactor
=======
>>>>>>> parent of 5385397... before refactor
}

void sdlIO::flush() {
 SDL_GL_SwapWindow(sdlIO::window);
  //SDL_RenderPresent(displayRenderer);
}

void sdlIO::eventLoop() {

    SDL_Event event;
    float rot = 0, tr = 0;
    //SDL_EnableKeyRepeat(300, 30);
<<<<<<< HEAD
<<<<<<< HEAD
   	
	
	while (!engineState::getInstance()->exit()) {
		/*while (SDL_PollEvent(& event)) {
=======
=======
>>>>>>> parent of 5385397... before refactor
    while (!this->exit) {


        while (SDL_PollEvent(& event)) {
<<<<<<< HEAD
>>>>>>> parent of 5385397... before refactor
=======
>>>>>>> parent of 5385397... before refactor
            if (event.type == SDL_QUIT) {
				engineState::getInstance()->setExit(true);
            }
<<<<<<< HEAD
<<<<<<< HEAD
	   }*/
    }
}

 void sdlIO::operator()() {
	 this->eventLoop();
 }

=======


            this->renderer_i->render();
        }
    }
}

>>>>>>> parent of 5385397... before refactor
=======
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


            this->renderer_i->render();
        }
    }
}

>>>>>>> parent of 5385397... before refactor
sdlIO::~sdlIO() {
    SDL_Quit();
}