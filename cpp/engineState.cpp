#include "engineState.hpp"

engineState::engineState() {
 global_exit=false;
 light=false;
}

void engineState::setExit(bool exit) {
	global_exit=exit;
}

bool engineState::exit() {
	return global_exit;
}

void engineState::set(char * key,void *setting) {
	this->settings[key]=setting;
}

void * engineState::get(char * key) {
	if (settings.find(key) == settings.end()) {
		return 0;
	} else {
		return this->settings[key];
	}
}

