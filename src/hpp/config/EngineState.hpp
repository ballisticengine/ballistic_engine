#ifndef EngineState_HPP
#define EngineState_HPP

#include "misc/singleton.hpp"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class EngineState : public Singleton<EngineState> {
protected:
    map<string, string> string_settings;
    map<string, bool> bool_settings;

public:
    void setBool(string key, bool setting);
    void setString(string key, string setting);
    bool getBool(string key);
    string getString(string string);
    void toggleBool(string key);
    EngineState();
};

#endif