#ifndef ENGINESTATE_HPP
#define ENGINESTATE_HPP

#include "singleton.hpp"
#include <map>
#include <iostream>

using namespace std;

class engineState : public singleton<engineState> {
protected:
	bool global_exit;
	map<char *,void *> settings;
	
public:
	bool debug_visual,lighting,noclip,keypress;
	void set(char * key,void *setting);
	void * get(char * key);
	void * toggle(char *key);
	engineState();
	void setExit(bool exit);
	bool exit();
	bool light;

};

#endif