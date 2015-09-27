#include "RenderingManagerInterface.hpp"

RenderingManagerInterface::RenderingManagerInterface() {
}


RenderingManagerInterface::~RenderingManagerInterface() {
}

void RenderingManagerInterface::setRenderer(RendererInterface *renderer) {
    this->renderer = renderer;
}

RendererInterface * RenderingManagerInterface::getRenderer() {
    return this->renderer;
}

void RenderingManagerInterface::setFlush(flush_function flush_callback) {
    this->flush_callback = flush_callback;
}