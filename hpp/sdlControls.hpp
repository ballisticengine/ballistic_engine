#ifndef SDLCTRL_H
#define SDLCTRL_H

#include <iostream>
#include <SDL/SDL.h>
#include <boost/thread/thread.hpp>

using namespace std;

#include "engineState.hpp"
#include "singleton.hpp"



class sdlControls : public singleton<sdlControls> {
public:
	void operator()();
};

#endif