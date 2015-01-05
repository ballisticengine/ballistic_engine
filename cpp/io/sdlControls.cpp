#include "io/sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
   e_loc f = PI / 180.0;
   return deg*f ;
}

void sdlControls::operator()() {
	
	ObserverEntity *o=world::getInstance()->getObserver();
	e_loc step=0.09,rstep=0.1,vstep=50;
	static e_loc rotx=0;
	static e_loc z=0;
	e_loc xx; 
	int x,y,winw=config::getInstance()->getVD()->width/2,winh=config::getInstance()->getVD()->height/2;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	TrRot vel;
	while(!engineState::getInstance()->exit()) {
	 const Uint8 *state = SDL_GetKeyboardState(NULL);
	 SDL_GetRelativeMouseState(&x,&y);
	 xx=0;
	
	 xx=x;
	 rotx+=x;
	
	 rotx=normalizeRotation(rotx);
	
	vel=o->getVelocity();
	camera *c=o->getCamera();
	//o->printVelocity();
	vel.reset();
	 
	 if(state[SDL_SCANCODE_W]) {
		vel.t.y=-vstep;
	 } 
	
	if(state[SDL_SCANCODE_S]) {
		vel.t.y=vstep;
	 }

	 if(state[SDL_SCANCODE_RIGHT]) {
		 vel.t.x+=-cos(deg2rad(rotx))*vstep;
		 vel.t.z+=-sin(deg2rad(rotx))*vstep;
		// o->bobHead();
	 }
	 
	 if(state[SDL_SCANCODE_LEFT]) {
		 vel.t.x+=cos(deg2rad(rotx))*vstep;
		 vel.t.z+=sin(deg2rad(rotx))*vstep;
		 //o->bobHead();
	 }

	 if(state[SDL_SCANCODE_UP]) {
		
		 vel.t.x+=-sin(deg2rad(rotx))*vstep;
		 vel.t.z+=cos(deg2rad(rotx))*vstep;
		 //o->bobHead();
	 }

	 if(state[SDL_SCANCODE_DOWN]) {
		 vel.t.x+=sin(deg2rad(rotx))*vstep;
		 vel.t.z+=-cos(deg2rad(rotx))*vstep;
		// o->bobHead();
	 }
        
	 
	 o->setVelocity(vel);
	 o->rotate(0,(e_loc)xx,0);
	 o->rotate((e_loc)y,0,0);
	
	
	}
	
}