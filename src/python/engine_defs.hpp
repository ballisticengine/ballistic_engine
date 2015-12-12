#ifndef ENGINE_DEFS_HPP
#define	ENGINE_DEFS_HPP
#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include "config/EngineState.hpp"
#include "resources/ResourceManager.hpp"


using namespace std;
using namespace boost;

namespace bp = boost::python;

void init_engine();

#endif	

