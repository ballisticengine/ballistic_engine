#include "engineState.hpp"

engineState::engineState() {
 global_exit=false;
}

void engineState::setExit(bool exit) {
	global_exit=exit;
}

bool engineState::exit() {
	return global_exit;
}