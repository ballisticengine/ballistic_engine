#include "time/timer.hpp"
Timer::Timer() {
 
}

void Timer::start() {
 clock_gettime( CLOCK_REALTIME, &s);
}

void Timer::stop() {
  clock_gettime( CLOCK_REALTIME, &e);
}

time_int Timer::getDiff() {
     
   timespec temp;
	if ((e.tv_nsec-s.tv_nsec)<0) {
		temp.tv_sec = e.tv_sec-s.tv_sec-1;
		temp.tv_nsec = 1000000000+e.tv_nsec-s.tv_nsec;
	} else {
		temp.tv_sec = e.tv_sec-s.tv_sec;
		temp.tv_nsec = e.tv_nsec-s.tv_nsec;
	}
	time_int diff=( temp.tv_sec + temp.tv_nsec);
    return this->ticksToSec(diff);
}

time_int Timer::getDiffR() {
    
    stop();
    
    time_int r=getDiff();
    ///cout << r << endl;
    start();
    return r;
}

time_int Timer::getDiffNR() {
    //time_int r = this->getDiff();
   // return this->ticksToSec(r);
}

time_int Timer::ticksToSec(time_int ts) {
  
    return ts/ 10000000L;
}