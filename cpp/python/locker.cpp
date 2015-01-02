#include "python/locker.hpp"


void PyLocker::lock() {
	state = PyGILState_Ensure();
}

void PyLocker::unlock() {
	PyGILState_Release(state);
}