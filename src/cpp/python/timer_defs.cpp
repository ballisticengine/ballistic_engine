#include "python/timer_defs.hpp"
#include "python/null_deleter.hpp"

BOOST_PYTHON_MODULE(Timer) {
    bp::class_<Timer, Timer*>("Timer")
            .def("start", &Timer::start)
            .def("stop", &Timer::stop)
            .def("getDiff", &Timer::getDiff)
            .def("getDiffR", &Timer::getDiffR)
            .def("getDiffNR", &Timer::getDiffNR)

            ;
};

void init_timer() {
    initTimer();
}