#ifndef STATEHANDLER_HPP
#define	STATEHANDLER_HPP

#include <iostream>

using namespace std;

enum StateType {
    STATE_STRING,
    STATE_BOOL,
    STATE_PTR
};

struct StateChangeData {
    StateType type;
    void *value;
    string key;
};

class StateHandler {
public:
    virtual void before(StateChangeData data) {};
    virtual void after(StateChangeData data) {};
};

#endif	

