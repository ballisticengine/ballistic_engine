#include "renderer/RenderingAction.hpp"

RenderingAction::RenderingAction() {

}

void RenderingAction::setWorld(World *w) {
    this->world = w;
}

void RenderingAction::setRenderer(RendererInterface *ri) {
    this->renderer = ri;
}

void RenderingAction::renderWithDecorators() {
    if(this->decorator) {
        this->decorator->before();
        this->render();
        this->decorator->after();
    } else {
        this->render();
    }
}

void RenderingAction::setDecorator(RenderingActionDecorator *decorator) {
    this->decorator = decorator;
}