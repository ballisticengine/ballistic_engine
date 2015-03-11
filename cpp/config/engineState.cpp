#include "config/EngineState.hpp"

EngineState::EngineState() {
 global_exit=false;
 debug_visual=false;
 lighting=true;
 noclip=false;

}

void EngineState::setExit(bool exit) {
	global_exit=exit;
}

bool EngineState::exit() {
 return global_exit;
}