#include "anim/animator.hpp"

Animator::Animator() {
	state=EngineState::getInstance();
}

void Animator::start() {
	boost::thread(boost::ref(*this));
	stop_animation=false;
}

void Animator::stop() {
	stop_animation=true;
}

void Animator::operator()() {
	while(!(stop_animation || state->getBool("exit"))) {
		animate();
	}
}
