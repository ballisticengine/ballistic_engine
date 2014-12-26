#include "shape2d.hpp"

Shape2d::Shape2d(e_loc width,e_loc height) {
	this->vertices=new v_type[4];
	this->uvs=new uv[4];
	e_loc 
		minx=-width/2,
		maxx=width/2,
		miny=height/2,
		maxy=-height/2
		;

	vertices[0].z=vertices[1].z=vertices[2].z=vertices[3].z=0;
	vertices[3].x=minx;  vertices[3].y=miny;
	vertices[2].x=maxx;  vertices[2].y=miny;
	vertices[1].x=maxx;  vertices[1].y=maxy;
	vertices[0].x=minx;  vertices[0].y=maxy;

	uvs[0].u=0; uvs[0].v=0;
	uvs[1].u=1; uvs[1].v=0;
	uvs[2].u=1; uvs[2].v=1;
	uvs[3].u=0; uvs[3].v=1;
	this->v_count=4;

}