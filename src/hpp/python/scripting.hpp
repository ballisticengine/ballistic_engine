
#ifndef SCRIPTING_HPP
#define	SCRIPTING_HPP

#include <string>
#include <iostream>
#include <vector>
#include <queue>

#include "python/manipulator.hpp"
#include "python/world_defs.hpp"
#include "python/hud_defs.hpp"
#include "python/timer_defs.hpp"
#include "python/engine_defs.hpp"
#include "config/EngineState.hpp"


using namespace std;

typedef  vector<PyManipulator *> man_list;

struct SignalType {
    string name;
    void *paramA,*paramB,*paramC,*paramD;
};

class PyScripting : public Singleton<PyScripting> {
protected:
	man_list manipulators;
        queue<SignalType> sig_queue;
        bool processing,other_bcast;
        boost::mutex m;
        
public:
	PyScripting();
	void operator()();
        void broadcast(string name,void *paramA=0,void *paramB=0,void* paramC=0,void* paramD=0);
	void broadcastInit();
	~PyScripting();
	void loadManipulators();
};


#endif	

