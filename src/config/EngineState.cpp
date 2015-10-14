#include "config/EngineState.hpp"

EngineState::EngineState() {

}

void EngineState::setBool(string key, bool setting) {
    bool_settings[key] = setting;
    this->processHandlers(key);
}

void EngineState::setString(string key, string setting) {
    string_settings[key] = setting;
    this->processHandlers(key);
}

bool EngineState::getBool(string key) {

    return bool_settings[key];
}

string EngineState::getString(string key) {
    return string_settings[key];
}

void EngineState::toggleBool(string key) {
    bool_settings[key] = !bool_settings[key];
}

void EngineState::processHandlers(string key) {
    StateChangeData data;
    
    if(!handlers[key]) {
        return;
    }
    
    if(string_settings.count(key)) {
        data.value = &string_settings[key];
        data.type = STATE_STRING;
    }
    if(bool_settings.count(key)) {
        data.value = &bool_settings[key];
        data.type = STATE_BOOL;
    }
    
    state_change_callback callback = handlers[key];
    callback(data);
    
    
}

void EngineState::setStateHandler(string key, state_change_callback callback) {
    this->handlers[key] = callback;
}

void EngineState::deleteStateHandler(string name) {
    
}