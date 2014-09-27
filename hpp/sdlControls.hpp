#ifndef SDLCTRL_H
#define SDLCTRL_H

#include <iostream>

#include <SDL/SDL.h>
#include <boost/thread/thread.hpp>
#include <cmath>

using namespace std;

#include "engineState.hpp"
#include "singleton.hpp"
#include "world.hpp"
#include "config.hpp"
#include "types.hpp"
#include "mathTypes.hpp"
#include "observerEntity.hpp"

#define PI 3.14159265

e_loc deg2rad(e_loc deg);



class sdlControls : public singleton<sdlControls> {
public:
	void operator()();
};

#endif