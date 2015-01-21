#ifndef LOCKER_HPP
#define	LOCKER_HPP
#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1


#include <boost/python.hpp>
#include "misc/singleton.hpp"
#include <iostream>
#include <map>
using namespace std;

class PyLocker : public singleton<PyLocker> {
    PyGILState_STATE state;
   
public:
    PyLocker();
    void lock();
    void unlock();
};

#endif	/* LOCKER_HPP */

