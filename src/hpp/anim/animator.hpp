#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <boost/thread/thread.hpp>


using namespace std;

#include "config/EngineState.hpp"

class Animator {
protected:
	EngineState *state;
	bool stop_animation;
	
	virtual void animate()=0;
public:
	Animator();
	virtual void start();
	virtual void stop();
	void operator()();
	
};

#endif