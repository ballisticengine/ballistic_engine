#include "timer.hpp"
#ifdef _WIN32

Timer::Timer() {
	QueryPerformanceFrequency( &frequency );
	 b.QuadPart=0;
     e.QuadPart=0; 
}

void Timer::start() {
	QueryPerformanceCounter(&b) ;
}

void Timer::stop() {
	QueryPerformanceCounter(&e);
}

time_int Timer::getDiff() {
	diff.QuadPart=e.QuadPart-b.QuadPart;
	return this->ticksToSec(diff);
}

time_int Timer::getDiffR() {
	this->stop();
	time_int r=this->getDiff();
	this->start();
	return r;
}

time_int Timer::ticksToSec(LARGE_INTEGER &ts) {
	return ((double)ts.QuadPart /(double)frequency.QuadPart) ;
}

#else 

Timer::Timer() {
	QueryPerformanceFrequency( &frequency );
	 b.QuadPart=0;
     e.QuadPart=0; 
}

void Timer::start() {
	gettimeofday(&b) ;;
}

void Timer::stop() {
	gettimeofday(&e) ;;
}

time_int Timer::getDiff() {
	diff=e.tv_usec-b.tv_usec;
	return this->ticksToSec(diff);
}

time_int Timer::getDiffR() {
	this->stop();
	time_int r=this->getDiff();
	this->start();
	return r;
}

time_int Timer::ticksToSec(time_int &ts) {
    return diff*1000*1000;
}

#endif