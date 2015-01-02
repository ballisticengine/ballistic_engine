
#ifndef SCRIPTING_HPP
#define	SCRIPTING_HPP

#include <string>
#include <iostream>
#include <vector>

#include "python/manipulator.hpp"
#include "python/world_defs.hpp"



using namespace std;

typedef  vector<PyManipulator *> man_list;

class PyScripting : public singleton<PyScripting> {
protected:
	man_list manipulators;
public:
	PyScripting();
	void broadcast(string name,void *paramA=0,void *paramB=0,void* paramC=0,void* paramD=0);
	void broadcastInit();
	~PyScripting();
	void loadManipulators();
};


#endif	

