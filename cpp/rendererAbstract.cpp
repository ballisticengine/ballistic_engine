#include "rendererAbstract.hpp"
#include "types.hpp"

renderer::renderer() {
    
}

renderer::~renderer() {
    
}

void renderer::init(videoData vd) {
    this->vd=vd;
    
} 

void renderer::setFlush(flushf flush_callback) {
    this->flush_callback=flush_callback;
}

void renderer::renderShape(shape *s) {
    tris_list tris;
        tris=s->getTris();    
    for (int i=0; i<tris.size(); i++) {
        for(int n=0; n<3; n++) {
            this->renderVertex(tris[i]->v[n]);
        }
    }
}