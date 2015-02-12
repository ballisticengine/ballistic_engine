#include "config/engineState.hpp"

engineState::engineState() {
 global_exit=false;
 debug_visual=false;
 lighting=true;
 noclip=false;

}

void engineState::setExit(bool exit) {

	global_exit=exit;
}

bool engineState::exit() {
 return global_exit;
}