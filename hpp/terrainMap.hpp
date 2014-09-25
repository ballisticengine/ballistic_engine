#ifndef TERRAIN_H

#define TERRAIN_H

#include <string>
#include <cmath>

using namespace std;

#include "entity.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "textureFactory.hpp"
#include "shapeFactory.hpp"


class TerrainMap {
protected:
	shape *quads,*s;
	texture * tex, * terrain;
	shapeFactory *sf;
	textureFactory *tf;
	int w,h,qc;
	void mapTerrain();

public:
	TerrainMap(string terrain_texture,string surface_texture);
	~TerrainMap();
	shape * getShape();
	texture *getTexture();
	shape *getQuads();
	int getQuadCount();
	int getW();
	int getH();
};

#endif
