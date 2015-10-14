#include "misc/State.hpp"

State::State() {
}

State::~State() {
}

void State::setBool(string key, bool setting) {
    bool_settings[key] = setting;
    this->processHandlers(key);
}

void State::setString(string key, string setting) {
    string_settings[key] = setting;
    this->processHandlers(key);
}

bool State::getBool(string key) {

    return bool_settings[key];
}

string State::getString(string key) {
    return string_settings[key];
}

void State::toggleBool(string key) {
    bool_settings[key] = !bool_settings[key];
}

void State::processHandlers(string key) {
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

void State::setStateHandler(string key, state_change_callback callback) {
    this->handlers[key] = callback;
}

void State::deleteStateHandler(string name) {
    
}