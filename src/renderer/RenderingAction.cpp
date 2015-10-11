#include "renderer/RenderingAction.hpp"

RenderingAction::RenderingAction() {

}

void RenderingAction::setWorld(World *w) {
    this->world = w;
}

void RenderingAction::setRenderer(RendererInterface *ri) {
    this->renderer = ri;
}