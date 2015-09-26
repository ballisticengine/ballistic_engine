#include "config/EngineState.hpp"

EngineState::EngineState() {

}

void EngineState::setBool(string key, bool setting) {
    bool_settings[key]=setting;
}

void EngineState::setString(string key, string setting) {
    string_settings[key]=setting;
}

bool EngineState::getBool(string key) {
//    if (bool_settings.count(key)==0) {
//        
//    }
    return bool_settings[key];
}

string EngineState::getString(string key) {
    return string_settings[key];
}

void EngineState::toggleBool(string key) {
    bool_settings[key]=!bool_settings[key];
}
