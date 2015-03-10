#ifndef EngineState_HPP
#define EngineState_HPP

#include "misc/singleton.hpp"
#include <map>
#include <iostream>

using namespace std;

class EngineState : public Singleton<EngineState> {
protected:
	bool global_exit;
	map<char *,void *> settings;
	
public:
	bool debug_visual,lighting,noclip,keypress,fullscreen,desktop_fs;
	void set(char * key,void *setting);
	void * get(char * key);
	void * toggle(char *key);
	EngineState();
	void setExit(bool exit);
	bool exit();
	bool light;

};

#endif