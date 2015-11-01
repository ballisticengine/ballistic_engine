#ifndef STATE_HPP
#define	STATE_HPP

#include <map>
#include <string>

#include "misc/StateHandler.hpp"

using namespace std;



typedef void (*state_change_callback)(StateChangeData);

class State {
protected:
    map<string, string> string_settings;
    map<string, bool> bool_settings;
    map<string, void *> ptr_settings;
    map<string, StateHandler*> handlers;
    void processHandlers(string key);
public:
    void setBool(string key, bool setting);
    void setString(string key, string setting);
    void setPtr(string key, void *ptr);
    bool getBool(string key);
    string getString(string string);
    void * getPtr(string key);
    void toggleBool(string key);
    void setStateHandler(string key, StateHandler *handler);
    void deleteStateHandler(string name);
    State();
    virtual ~State();
};

#endif

