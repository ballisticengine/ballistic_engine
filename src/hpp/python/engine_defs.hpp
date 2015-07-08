#ifndef ENGINE_DEFS_HPP
#define	ENGINE_DEFS_HPP
#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>

#include "engine.hpp"

using namespace std;
using namespace boost;

void init_engine();

#endif	

