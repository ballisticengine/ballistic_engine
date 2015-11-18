#ifndef MANIPULATOR_HPP
#define	MANIPULATOR_HPP

#include <string>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <initializer_list>

#include "entities/entity.hpp"
#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "misc/utils.hpp"
#include "python/ScriptBase.hpp"
#include "python/locker.hpp"

namespace bp = boost::python;
using namespace std;
using namespace boost;

class PyManipulator : public ScriptBase {
protected:

    string classname, iname;
    bp::object instance;
    template <typename T> static bp::list arrayToList(T *array);
    void lockThreads();
    void unlockThreads();
public:
    bool hasSignal(string name);
    
    /*
     * Tests if signal invocation doesn't cause exception
     * Not implemented
     */
    bool testSignal(string name, initializer_list<void *> params);
    PyManipulator(string filename);
    void signal(string name, initializer_list<void *> params, bool ui_signal=false);
};



#endif	

