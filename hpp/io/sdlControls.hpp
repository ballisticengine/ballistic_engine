#ifndef SDLCTRL_H
#define SDLCTRL_H

#include <iostream>

#ifdef __WIN32__
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <boost/thread/thread.hpp>
#include <cmath>

using namespace std;

#include "config/EngineState.hpp"
#include "misc/singleton.hpp"
#include "world/World.hpp"
#include "config/Config.hpp"
#include "types/types.hpp"
#include "types/mathTypes.hpp"
#include "entities/observerEntity.hpp"
#include "io/keyTypes.hpp"
#include "python/scripting.hpp"


#define PI 3.14159265

e_loc deg2rad(e_loc deg);



class SdlControls : public Singleton<SdlControls> {
    size_t anykey(const Uint8 *state,int ksize);
public:
	void operator()();
};

#endif