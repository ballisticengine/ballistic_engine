#include "timer.hpp"

Timer::Timer() {
	QueryPerformanceFrequency( &frequency );
}