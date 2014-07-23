#include "rendererAbstract.hpp"
#include "types.hpp"

renderer::renderer() {

}

renderer::~renderer() {

}

void renderer::init(videoData vd) {
    frustum_start = 100;
    frustum_end = 100000;
    frustum_x = 200;
    frustum_y = 200;
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

void renderer::setFlush(flushf flush_callback) {
    this->flush_callback = flush_callback;
}

void renderer::renderPShape(shape *s) {
    vert_list verts = s->getVertices();
   
    for (int i = 0; i < verts.size(); i++) {
        this->renderVertex(verts[i]);
    }
}

void renderer::renderShape(shape *s) {
    tris_list tris;
    tris = s->getTris();
    for (int i = 0; i < tris.size(); i++) {
        for (int n = 0; n < 3; n++) {
            this->renderVertex(tris[i]->v[n]);
        }
    }
}

void renderer::operator()() {
    while (1) {
        this->render();
    }
}

void renderer::translate(float x, float y, float z) {
    gx=x;
    gy=y;
    gz=z;
}

void renderer::rotate(float x) {
    gr=x;
}