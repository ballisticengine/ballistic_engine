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

#ifdef __WIN32__
#include <boost/smart_ptr/make_shared_array.hpp>
#else
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>
#endif
namespace bp=boost::python;

#include "misc/singleton.hpp"
#include "config/config.hpp"
#include "misc/utils.hpp"
#include "entities/entity.hpp"
#include "entities/physicalEntity.hpp"
#include "entities/weapon.hpp"
#include "entities/sprite.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/mathTypes.hpp"
#include "world/world.hpp"
//#include "pyVector.hpp"

using namespace std;
using namespace boost;




void init_world();






#endif