#include "rendererAbstract.hpp"
#include "types.hpp"

renderer::renderer() {

}

renderer::~renderer() {

}

void renderer::init(videoData vd) {
	config *c=config::getInstance();
	frustum_start = c->getVD()->frustum_start;
	frustum_end = c->getVD()->frustum_end;
	frustum_x = c->getVD()->frustum_x;
	frustum_y = c->getVD()->frustum_y;
    this->vd = vd;
    this->w = (world *) world::getInstance();
    skybox *sky = this->w->getSkybox();

    sky->makeShape(frustum_x, frustum_y);
   
    gx=0;
    gy=0;
    gz=0;
    gr=0;
     this->specificInit();

}

 void  renderer::translate(coords c) {
	 this->translate(c.x,c.y,c.z);
 }

void renderer::renderAllEntities() {
	obj_list ents=w->getModels();
	for(int i=0; i<ents.size(); i++) {
		
		coords c=ents[i]->getCoords();
		this->translate(c.x,c.y,c.z);
		this->renderShape(ents[i]->getModel());
		
	}
}

void renderer::setFlush(flushf flush_callback) {
    this->flush_callback = flush_callback;
}

void renderer::renderPShape(shape *s) {
    vert_list verts = s->getVertices();
   
	this->begin();
	for (int i = 0; i < verts.size(); i++) {
        this->renderVertex(verts[i]);
    }
	this->end();
}

void renderer::renderShape(shape *s) {
    tris_list tris;
  
	tris = s->getTris();

    this->begin();
	for (int i = 0; i < tris.size(); i++) {
       
		for (int n = 0; n < 3; n++) {
            this->renderVertex(tris[i]->v[n]);
        }
    }
	this->end();
}

void renderer::operator()() {
    while (1) {
        this->render();
    }
}

