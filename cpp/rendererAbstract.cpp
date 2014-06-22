#include "rendererAbstract.hpp"

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