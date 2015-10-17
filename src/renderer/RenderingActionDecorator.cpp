#include "renderer/RenderingActionDecorator.hpp"

void RenderingActionDecorator::setRenderer(RendererInterface *renderer_interface) {
    this->renderer_interface = renderer_interface;
}

void RenderingActionDecorator::setData(void *data) {
    this->data = data;
}

void *RenderingActionDecorator::getData() {
    return this->data;
}