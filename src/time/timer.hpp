#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <cstdio>

using namespace std;
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
#include <boost/timer/timer.hpp>
#include <boost/chrono/chrono.hpp>

using boost::timer::nanosecond_type;
using boost::timer::cpu_times;
using boost::timer::cpu_timer;
using boost::timer::auto_cpu_timer;

class Timer {
protected:
    timespec s,e;
    
 time_int diff;
	time_int ticksToSec(time_int ts);
public:
	Timer();
	void start();
	void stop();
	time_int getDiff();
	time_int getDiffR();
        time_int getDiffNR();

};
#endif
#endif