#ifndef EngineState_HPP
#define EngineState_HPP

#include "misc/singleton.hpp"
#include <map>
#include <string>
#include <iostream>

using namespace std;

enum StateType {
    STATE_STRING,
    STATE_BOOL
};

/*
 Data passed to callback
 */
struct StateChangeData {
    StateType type;
    void *value;
    string key;
};


//struct StateHandler {
//    state_change_callback callback;
//    string name;
//};


typedef void (*state_change_callback)(StateChangeData);

class EngineState : public Singleton<EngineState> {
protected:
    map<string, string> string_settings;
    map<string, bool> bool_settings;
    map<string, state_change_callback> handlers;
    void processHandlers(string key);
public:
    void setBool(string key, bool setting);
    void setString(string key, string setting);
    bool getBool(string key);
    string getString(string string);
    void toggleBool(string key);
    void setStateHandler(string key, state_change_callback callback);
    void deleteStateHandler(string name);
    EngineState();
};

#endif