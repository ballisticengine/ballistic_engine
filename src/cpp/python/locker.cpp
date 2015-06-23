#include "python/locker.hpp"


PyLocker::PyLocker() {
    
}

void PyLocker::lock() {
  
    state = PyGILState_Ensure();
  
}

void PyLocker::unlock() {
  
    PyGILState_Release(state);
  
}