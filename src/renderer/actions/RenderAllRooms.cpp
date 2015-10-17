#include "renderer/actions/RenderAllRooms.hpp"

void RenderAllRooms::render() {
     rooms_list rooms = world->rooms;
    size_t rooms_size = rooms.size();
    for (size_t i = 0; i < rooms_size; i++) {
        Coords rc = rooms[i]->getCoords();
        this->renderer->resetMatrix();
        this->renderer->setDrawColor(ColorRGBA(rooms[i]->id));
        
        this->renderer->positionCamera(world->getObserver()->getCamera());
        this->renderer->translate(rc.translation);
        this->renderer->face(rc.rotation);
        this->renderer->renderShape((Shape *) rooms[i]->getModel());
    }
}
