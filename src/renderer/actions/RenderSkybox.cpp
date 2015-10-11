#include "renderer/actions/RenderSkybox.hpp"

void RenderSkybox::render() {
    this->renderer->renderSkybox(world->sky);
}