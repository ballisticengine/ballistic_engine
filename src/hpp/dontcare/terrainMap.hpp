#ifndef TERRAIN_H

#define TERRAIN_H

#include <string>
#include <cmath>

using namespace std;

#include "entities/entity.hpp"
#include "types/texture.hpp"
#include "types/types.hpp"
#include "factories/textureFactory.hpp"
#include "factories/shapeFactory.hpp"


class TerrainMap {
protected:
	Shape *quads,*s;
	Texture * tex, * terrain;
	ShapeFactory *sf;
	TextureFactory *tf;
	int w,h,qc;
	void mapTerrain();

public:
	TerrainMap(string terrain_texture,string surface_texture);
	~TerrainMap();
	Shape * getShape();
	Texture *getTexture();
	Shape *getQuads();
	int getQuadCount();
	int getW();
	int getH();
};

#endif
