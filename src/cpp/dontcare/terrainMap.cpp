#include "dontcare/terrainMap.hpp"

void TerrainMap::mapTerrain() {
	unsigned char * pixels=(unsigned char *)this->terrain->getPixels();
	int width=this->terrain->getWidth(),
		height=this->terrain->getHeight()
		;



	int m_width=5,m_height=5;
	e_loc x,y,z,step=0.1; //*m_height;
	qc=m_width*m_height;
	qc=qc*(qc/step);

	quads=new shape[qc];
	vector <vertex *> vs;

	

	x=y=z=0;
	w=h=0;
	int vi=0,pi=0;
	for(e_loc i=0; i<m_height; i+=step) {
		x=0;
		h++;
		for(e_loc n=0; n<m_width; n+=step) {
			if(h==1) {
				w++;
			}
			//e_loc zz=pixels[vi];
			vertex *v1=new vertex(n,i,0),
				*v2=new vertex(n+step,i,0),
				*v3=new vertex(n,i+step,0),
				*v4=new vertex(n+step,i+step,0)
				;
			quads[vi].addVertex(v1);
			quads[vi].addVertex(v2);
			quads[vi].addVertex(v4);
			quads[vi].addVertex(v3);
			vs.push_back(v1);
			vs.push_back(v2);
			vs.push_back(v3);
			vs.push_back(v4);
			vi++;
		}	
	}
	cout << "Width: " << w << ", Height: " << h << endl;

	vi=w;
	pi=0;
	
	for(int i=1; i<h; i++) {
		for(int n=1; n<w; n++) {
			
			vert_list verts=quads[vi].getVertices(),
				beforey_verts=quads[vi-w].getVertices(),
				beforex_verts=quads[vi-1].getVertices()
				;
			for(int ix=0; ix<3; ix++) {
				beforex_verts[ix]->z=beforey_verts[ix]->z=verts[ix]->z=pixels[pi]/100;
			}
			vi++;
			pi++;
		}
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