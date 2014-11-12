#ifndef PYTHONSCRIPTS_H
#define PYTHONSCRIPTS_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>

namespace bp=boost::python;

#include "singleton.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include "types.hpp"
#include "light.hpp"
#include "mathTypes.hpp"
#include "world.hpp"
//#include "pyVector.hpp"

using namespace std;


class PyLocker : public singleton<PyLocker>{
	 PyGILState_STATE state;
public:
	void lock();
	void unlock();
};

class PyManipulator {
protected:
	char *code;
	string filename,classname,iname;
	bp::object module,instance;
public:
  PyManipulator(string file);
  void signal(string name,void *params);
  ~PyManipulator();
};


typedef  vector<PyManipulator *> man_list;

class PyScripting : public singleton<PyScripting> {
protected:
	man_list manipulators;
public:
	PyScripting();
	void broadcast(string name,void *params);
	void broadcastInit();
	~PyScripting();
	void loadManipulators();
};


#endif