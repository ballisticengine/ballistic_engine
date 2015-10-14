#ifndef EngineState_HPP
#define EngineState_HPP

#include <map>
#include <string>
#include <iostream>

using namespace std;

#include "misc/singleton.hpp"
#include "misc/State.hpp"




class EngineState : public State, public Singleton<EngineState> {

};

#endif