#ifndef TERRAIN_FACTORY_H

#define TERRAIN_FACTORY_H

#include "factories/factory.hpp"
#include "types/types.hpp"


class TerrainFactory: public factory, public singleton<TerrainFactory> {
protected:
	virtual void * actualLoad(string fn);
};
#endif

