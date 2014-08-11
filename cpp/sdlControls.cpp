#include "sdlControls.hpp"

void sdlControls::operator()() {
	while(!engineState::getInstance()->exit()) {
	 const Uint8 *state = SDL_GetKeyboardState(NULL);
	 if(state[SDL_SCANCODE_RIGHT]) {
	  cout << "RIGHT";
	 }

	}
}