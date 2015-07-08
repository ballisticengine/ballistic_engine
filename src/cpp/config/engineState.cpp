#include "config/EngineState.hpp"

EngineState::EngineState() {
 debug_visual=false;
 lighting=true;
 noclip=false;
 edit_mode=false;

}

void EngineState::setBool(string key, bool setting) {
    bool_settings[key]=setting;
}

void EngineState::setString(string key, string setting) {
    string_settings[key]=setting;
}

bool EngineState::getBool(string key) {
    return bool_settings[key];
}

string EngineState::getString(string key) {
    return string_settings[key];
}

void EngineState::toggleBool(string key) {
    bool_settings[key]=!bool_settings[key];
}
