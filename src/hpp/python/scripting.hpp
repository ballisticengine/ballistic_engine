
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
#include "python/hud_defs.hpp"
#include "python/timer_defs.hpp"
#include "python/renderer_defs.hpp"
#include "python/engine_defs.hpp"
#include "config/EngineState.hpp"


using namespace std;

typedef  vector<PyManipulator *> man_vector;
typedef  map<string name, PyManipulator *> man_map;

struct SignalType {
    string name;
    void *paramA,*paramB,*paramC,*paramD;
};

enum SignalName {
    ///Pass that to broadcast/signal instead of string
};

/*
 * Instead of sending signals by name from engine, send signals by type and
 * attach handler [Module.method] in PyScripting 
 */



class PyScripting : public Singleton<PyScripting> {
protected:
	man_vector manipulators;
        queue<SignalType> sig_queue;
        bool processing,other_bcast;
        boost::mutex m;
        
public:
	PyScripting();
	void operator()();
        void broadcast(string name, initializer_list<void *> params={});
	void broadcastInit();
        man_vector getManipulators();
        PyManipulator* getManipulator();
	~PyScripting();
	void loadManipulators();
};


#endif	

