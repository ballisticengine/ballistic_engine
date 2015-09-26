#ifndef LEVELMANAGER_HPP
#define	LEVELMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>

using namespace std;

#include "misc/singleton.hpp"
#include "config/path.hpp"
#include "types/Resource.hpp"
#include "libload/LibLoad.hpp"
#include "misc/utils.hpp"
#include "resources/Loader.hpp"
#include "resources/ResourceManager.hpp"


class LevelManager : public ResourceManager, public Singleton<LevelManager> {
    
};

#endif	

