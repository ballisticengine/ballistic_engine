#ifndef TIMER_H
#define TIMER_H


#include <windows.h>

typedef double time_int;

class Timer {
protected:
	LARGE_INTEGER b,e,diff,frequency;
	time_int ticksToSec(LARGE_INTEGER &ts);
public:
	Timer();
	void start();
	void stop();
	time_int getDiff();
	time_int getDiffR();

};

#endif