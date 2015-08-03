#ifndef HUDDEFS_H
#define HUDDEFS_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


#define BOOST_PYTHON_STATIC_LIB 1

#define BOOST_PYTHON_NO_LIB 1

#include <boost/python.hpp>

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/shared_ptr.hpp>


namespace bp=boost::python;

#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "misc/utils.hpp"
#include "ui/hud.hpp"
#include "ui/image.hpp"
#include "ui/uiMesh.hpp"
#include "types/texture.hpp"
//#include "pyVector3d.hpp"

using namespace std;
using namespace boost;

void init_hud();

#endif