#include "renderer/actions/RenderAllEntities.hpp"

void RenderAllEntities::render() {
    obj_list ents = world->active_room->models;
    size_t ents_size = ents.size();
    for (size_t i = 0; i < ents_size; i++) {
        Coords c = ents[i]->getCoords();
        this->renderer->resetMatrix();
        this->renderer->positionCamera(world->getObserver()->getCamera());
        this->renderer->translate(c.translation);
        this->renderer->face(c.rotation);
        this->renderer->renderShape(ents[i]->getModel());

    }
}
