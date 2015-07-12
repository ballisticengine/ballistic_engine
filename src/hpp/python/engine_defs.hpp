#ifndef ENGINE_DEFS_HPP
#define	ENGINE_DEFS_HPP
#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>

#include "config/EngineState.hpp"
#ifdef __WIN32__
#include <boost/smart_ptr/make_shared_array.hpp>
#else
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>
#endif

using namespace std;
using namespace boost;

namespace bp = boost::python;

void init_engine();

#endif	
