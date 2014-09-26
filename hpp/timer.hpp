#ifndef TIMER_H
#define TIMER_H


#include <windows.h>

class Timer {
protected:
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
    LARGE_INTEGER stop;
public:
	Timer();
};

#endif