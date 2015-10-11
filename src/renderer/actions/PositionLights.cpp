#include "renderer/actions/PositionLights.hpp"

void PositionLights::render() {
    lights_list lights = world->active_room->lights;
    size_t lights_size = lights.size();

    for (size_t i = 0; i < lights_size; i++) {
        Coords lc = lights[i]->getCoords();
        this->renderer->resetMatrix();
        this->renderer->positionCamera(world->getObserver()->getCamera());
        this->renderer->translate(lc.translation);
        this->renderer->addLight(lights[i]);
    }
}