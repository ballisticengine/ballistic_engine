
#ifndef SCRIPTING_HPP
#define	SCRIPTING_HPP

#include <string>
#include <iostream>
#include <vector>
#include <queue>

#include "python/manipulator.hpp"
#include "python/world_defs.hpp"
#include "python/hud_defs.hpp"
#include "config/engineState.hpp"


using namespace std;

typedef  vector<PyManipulator *> man_list;

struct signal_type {
    string name;
    void *paramA,*paramB,*paramC,*paramD;
};

class PyScripting : public singleton<PyScripting> {
protected:
	man_list manipulators;
        queue<signal_type> sig_queue;
        bool processing,other_bcast;
        
public:
	PyScripting();
	void operator()();
        void broadcast(string name,void *paramA=0,void *paramB=0,void* paramC=0,void* paramD=0);
	void broadcastInit();
	~PyScripting();
	void loadManipulators();
};


#endif	

