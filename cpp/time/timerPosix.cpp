#include "time/timer.hpp"
Timer::Timer() {
 b.user=0;
    e.user=0;
    
    //clock_getres(CLOCK_REALTIME,&res);
}

void Timer::start() {
    //  start_timer.start();
    
    //end_timer.start();
    
    
}

void Timer::stop() {
    end_timer.stop();
}

time_int Timer::getDiff() {
     
    e=end_timer.elapsed();
    diff=(time_int)e.user;
    
    //cout << "Elapsed" << e.user << endl;
    //cout.flush();
        //printf("%lu\n",diff); 
       // fflush(stdout);
    //cout << diff.tv_usec << endl;
    return this->ticksToSec(diff);
}

time_int Timer::getDiffR() {
    this->stop();
    this->getDiff(); 
    time_int r = this->getDiff(); 
    //time_int r;
    //cout << r << endl;
    this->start();
  
    return r;
}

time_int Timer::getDiffNR() {
    //time_int r = this->getDiff();
   // return this->ticksToSec(r);
}

time_int Timer::ticksToSec(time_int ts) {
    //clock_getres(CLOCK_MONOTONIC,&res);
    //cout << res.tv_nsec << ", " << res.tv_sec << endl;
    //cout.flush();
    return ts/1000/1000/1000/1000/100;
}