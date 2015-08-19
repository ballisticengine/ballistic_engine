
#ifndef SCRIPTING_HPP
#define	SCRIPTING_HPP

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include "python/manipulator.hpp"
#include "python/type_defs.hpp"
#include "python/world_defs.hpp"
#include "python/timer_defs.hpp"
#include "python/renderer_defs.hpp"
#include "python/engine_defs.hpp"
#include "python/utils.hpp"
#include "config/EngineState.hpp"


using namespace std;

typedef vector<PyManipulator *> man_vector;
typedef map<string, PyManipulator *> man_map;

struct SignalType {
    string name;
    initializer_list<void *> params;
    bool check_existing;
};

enum SignalName {
    ///Pass that to broadcast/signal instead of string
};

/*
 * Instead of sending signals by name from engine, send signals by type and
 * attach handler [Module.method] in PyScripting 
 */

//better assign signals from python to concrete events
//like sdlio::assignSingnal or something

class PyScripting : public Singleton<PyScripting> {
protected:
    man_vector manipulators;
    man_map manipulators_map;
    queue<SignalType> sig_queue;
    bool processing, other_bcast;
    boost::mutex m;
    void lockWait();

public:
    PyScripting();
    void operator()();
    void broadcast(string name,
            initializer_list<void *> params = {}, bool check_existing = false);
    
    void enqueue(string name,
            initializer_list<void *> params = {}, bool check_existing = false);
    
    void clear_queue();
    void runQueue();
//    void broadcast(string name,
//            map<string,string> params, bool check_existing = false);
    void broadcastInit();
    man_vector getManipulatorsV();
    PyManipulator* getManipulator(string name);
    ~PyScripting();
    void loadManipulators();
};


#endif	

