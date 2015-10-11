#include "RenderingManagerInterface.hpp"

RenderingManagerInterface::RenderingManagerInterface() {
}


RenderingManagerInterface::~RenderingManagerInterface() {
}

void RenderingManagerInterface::setRenderer(RendererInterface *renderer) {
    this->renderer = renderer;
    for(auto a: actions) {
        a->setRenderer(renderer);
    }
}

RendererInterface * RenderingManagerInterface::getRenderer() {
    return this->renderer;
}

void RenderingManagerInterface::setFlush(flush_function flush_callback) {
    this->flush_callback = flush_callback;
}

 void RenderingManagerInterface::addAction(RenderingAction *action) {
     actions.push_back(action);
 }
 
 vector<RenderingAction *> RenderingManagerInterface::getActions() {
     return actions;
 }