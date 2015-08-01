#ifndef MANIPULATOR_HPP
#define	MANIPULATOR_HPP
#include <string>
#include <iostream>
#include <vector>

using namespace std;





#include <boost/python.hpp>
#include <boost/filesystem.hpp>



#include "entities/entity.hpp"
#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "misc/utils.hpp"
#include "ui/hud.hpp"


#include "python/locker.hpp"

namespace bp=boost::python;
using namespace std;
using namespace boost;

class PyManipulator {
protected:
	char *code;
	string filename,classname,iname;
	bp::object module,instance;
        template <typename T> static bp::list arrayToList(T *array);
public:
  PyManipulator(string file);
  void signal(string name,void *paramA=0,void *paramB=0,void* paramC=0,void* paramD=0);
  ~PyManipulator();
};



#endif	

