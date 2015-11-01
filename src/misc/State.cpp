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

void State::setPtr(string key, void *ptr) {
    ptr_settings[key]=ptr;
}

bool State::getBool(string key) {

    return bool_settings[key];
}

string State::getString(string key) {
    return string_settings[key];
}

void * State::getPtr(string key) {
    return ptr_settings[key];
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
    
    handlers[key]->after(data);
    
    
    
}

void State::setStateHandler(string key, StateHandler *handler) {
    this->handlers[key] = handler;
}

void State::deleteStateHandler(string name) {
    
}