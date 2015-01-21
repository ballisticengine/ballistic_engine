#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <boost/thread/thread.hpp>


using namespace std;

#include "config/engineState.hpp"

class Animator {
protected:
	engineState *state;
	bool stop_animation;
	
	virtual void animate()=0;
public:
	Animator();
	virtual void start();
	virtual void stop();
	void operator()();
	
};

#endif