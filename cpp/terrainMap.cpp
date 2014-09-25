#include "terrainMap.hpp"

void TerrainMap::mapTerrain() {
	unsigned char * pixels=(unsigned char *)this->terrain->getPixels();
	int width=this->terrain->getWidth(),
		height=this->terrain->getHeight()
	;
	
	
	
	int
		
		m_width=ceil((e_loc)width/20),
		m_height=ceil((e_loc)height/20);
	
	quads=new shape[m_width*m_height];
	qc=m_width*m_height;
	w=m_width;
	h=m_height;
	cout << "MH: " << m_height << endl;
	e_loc x,y,z,step_x=1,step_y=step_x;//*m_height;
	x=y=z=0;
	int l=0;
	for(int i=0; i<m_height; i++) {
	 x=0;
		for(int n=0; n<m_width; n++) {
		 vertex *v1=new vertex(x,y,z),
				*v2=new vertex(x+step_x,y,z),
				*v3=new vertex(x,y+step_y,z),
				*v4=new vertex(x+step_x,y+step_y,z)
			 ;
		 quads[l].addVertex(v2);
		 quads[l].addVertex(v1);
		 
		 quads[l].addVertex(v3);
		 quads[l].addVertex(v4);
		l++;
		 x+=step_x;
		
	 }
	 y+=step_y;
	}
}

TerrainMap::TerrainMap(string terrain_texture,string surface_texture) {
	this->tf=textureFactory::getInstance();
	this->s=new shape();
	this->sf=shapeFactory::getInstance();
	this->terrain=(texture *)(this->tf->get(terrain_texture));
	this->tex=(texture *)(this->tf->get(terrain_texture));
	this->mapTerrain();
}

TerrainMap::~TerrainMap() {
 delete this->s;
}

shape * TerrainMap::getShape() {
 return this->s;
}

texture * TerrainMap::getTexture() {
	return this->tex;
}

int TerrainMap::getW() {
 return w;
}

int TerrainMap::getH() {
 return h;
}

shape * TerrainMap::getQuads() {
 return quads;
}

int  TerrainMap::getQuadCount() {
 return qc;
}