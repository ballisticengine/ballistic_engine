#ifndef STATE_HPP
#define	STATE_HPP

#include <map>
#include <string>

using namespace std;

enum StateType {
    STATE_STRING,
    STATE_BOOL
};


struct StateChangeData {
    StateType type;
    void *value;
    string key;
};

typedef void (*state_change_callback)(StateChangeData);

class State {
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
    State();
    virtual ~State();
};

#endif

