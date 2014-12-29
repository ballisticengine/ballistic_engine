#include "timer.hpp"
Timer::Timer() {
   // QueryPerformanceFrequency(&frequency);
    e.tv_usec=0;
    b.tv_usec=0;
}

void Timer::start() {
    gettimeofday(&b,0);
}

void Timer::stop() {
    gettimeofday(&e,0);
}

time_int Timer::getDiff() {
    diff.tv_usec = e.tv_usec - b.tv_usec;
    return this->ticksToSec(((time_int)diff.tv_usec));
}

time_int Timer::getDiffR() {
    this->stop();
    time_int r = this->getDiff(); 
    this->start();
    return r;
}

time_int Timer::getDiffNR() {
    time_int r = this->getDiff();
    return this->ticksToSec(r);
}

time_int Timer::ticksToSec(time_int ts) {
    return ts * 1000 * 1000;
}