#ifndef TIMER_H
#define TIMER_H


typedef long double time_int;
#ifdef _WIN32
#include <windows.h>



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
	time_int getDiffNR();

};

#else
#include <sys/time.h>

class Timer {
protected:
	timeval b,e,diff,frequency;
	time_int ticksToSec(time_int &ts);
public:
	Timer();
	void start();
	void stop();
	time_int getDiff();
	time_int getDiffR();

};
#endif
#endif