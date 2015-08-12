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


namespace bp=boost::python;

#include "misc/singleton.hpp"
#include "config/Config.hpp"
#include "misc/utils.hpp"
#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "entities/weapon.hpp"
#include "entities/sprite.hpp"
#include "types/types.hpp"
#include "entities/light.hpp"
#include "types/Vector3d.hpp"
#include "types/boundingCube.hpp"
#include "world/World.hpp"
#include "physics/BulletPhysics.hpp"
//#include "pyVector3d.hpp"

using namespace std;
using namespace boost;




void init_world();






#endif