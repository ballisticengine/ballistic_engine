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
    map<string, double> number_settings;
    map<string, StateHandler*> handlers;
    void processHandlers(string key);
public:
    virtual void setBool(string key, bool setting);
    virtual void setString(string key, string setting);
    virtual void setPtr(string key, void *ptr);
    virtual void setNumber(string key, double n);
    virtual double getNumber(string key);
    virtual bool getBool(string key);
    virtual string getString(string string);
    virtual void * getPtr(string key);
    virtual void toggleBool(string key);
    virtual void setStateHandler(string key, StateHandler *handler);
    virtual void deleteStateHandler(string name);
    State();
    virtual ~State();
};

#endif

