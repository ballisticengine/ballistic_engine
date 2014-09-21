#include "sdlControls.hpp"

e_loc deg2rad(e_loc deg) {
   e_loc f = PI / 180.0;
   return deg*f ;
}

void sdlControls::operator()() {
	camera *c=world::getInstance()->getCurrentCamera();
	e_loc step=0.1,rstep=1;
	static e_loc rotx=0;
	static e_loc z=0;
	e_loc xx;
	int x,y,winw=config::getInstance()->getVD()->width/2,winh=config::getInstance()->getVD()->height/2;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while(!engineState::getInstance()->exit()) {
	 const Uint8 *state = SDL_GetKeyboardState(NULL);
	 SDL_GetRelativeMouseState(&x,&y);
	 xx=0;
	 /*if(x>0) {
	  rotx+=x;
	  xx=x;
	 } else if (x<0) {
	  rotx-=x;
	  xx=-x;
	 }*/
	 xx=x;
	 rotx+=x;
	 //rotx+=x;
	 rotx=normalizeRotation(rotx);
	 cout << rotx << ", " << x << endl;
	 if(state[SDL_SCANCODE_RIGHT]) {
		 //c->translate(-step,0,0);
		 c->translate(-cos(deg2rad(rotx))*step,0,-sin(deg2rad(rotx))*step);
	 }
	 
	 if(state[SDL_SCANCODE_LEFT]) {
	 	 c->translate(cos(deg2rad(rotx))*step,0,sin(deg2rad(rotx))*step);
	 }

	 if(state[SDL_SCANCODE_UP]) {
	 	
		 c->translate(-sin(deg2rad(rotx))*step,0,cos(deg2rad(rotx))*step);
	 }

	 if(state[SDL_SCANCODE_DOWN]) {
	 	
		 c->translate(sin(deg2rad(rotx))*step,0,-cos(deg2rad(rotx))*step);
		 //c->translate(0,0,-step);
	 }
	
	 c->rotate(0,(e_loc)xx,0);
	 c->rotate((e_loc)y,0,0);
	
	 SDL_Delay(10);
	}
	
}