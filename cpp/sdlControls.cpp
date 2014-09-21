#include "sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
   e_loc f = PI / 180.0;
   return deg*f ;
}

void sdlControls::operator()() {
	camera *c=world::getInstance()->getCurrentCamera();
	e_loc step=0.1;
	static e_loc rotx=0;
	static e_loc z=0;
	int x,y,winw=config::getInstance()->getVD()->width/2,winh=config::getInstance()->getVD()->height/2;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while(!engineState::getInstance()->exit()) {
	 const Uint8 *state = SDL_GetKeyboardState(NULL);
	 SDL_GetRelativeMouseState(&x,&y);
	  rotx+=x/2;
	 rotx=normalizeRotation(rotx);
	 
	 if(state[SDL_SCANCODE_RIGHT]) {
		 c->translate(-step,0,0);
	 }
	 
	 if(state[SDL_SCANCODE_LEFT]) {
	 	 c->translate(step,0,0);
	 }

	 if(state[SDL_SCANCODE_UP]) {
	 	
		 c->translate(-sin(deg2rad(rotx))*step,0,cos(deg2rad(rotx))*step);
	 }

	 if(state[SDL_SCANCODE_DOWN]) {
	 	
		 c->translate(-sin(deg2rad(rotx))*step,0,-cos(deg2rad(rotx))*step);
		 //c->translate(0,0,-step);
	 }
	
	 c->rotate(0,(e_loc)x/2,0);
	 c->rotate((e_loc)y/2,0,0);
	
	 SDL_Delay(10);
	}
	
}