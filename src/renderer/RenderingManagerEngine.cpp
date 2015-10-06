#include "renderer/RenderingManagerEngine.hpp"
void RenderingManagerEngine::setupTextures() {
    cout << "setupTextures" << endl;
    vector<LoadedResource *> ts = ResourceManager::getInstance()->getByType(TEXTURE);

    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) {

        if (ts[i]->object) {
            cout << "Stextures" << endl;
            this->renderer->setupTexture((Ballistic::Types::Texture *) ts[i]->object);
        }
    }
}

void RenderingManagerEngine::face(Vector3d &v) {
    this->renderer->rotate(Vector3d(1, 0, 0), v.x);
    this->renderer->rotate(Vector3d(0, 1, 0), v.y);
    this->renderer->rotate(Vector3d(0, 0, 1), v.z);
}

void RenderingManagerEngine::renderAllRooms() {
    rooms_list rooms = world->rooms;
    size_t rooms_size = rooms.size();
    for (size_t i = 0; i < rooms_size; i++) {
        Coords rc = rooms[i]->getCoords();
        this->renderer->resetMatrix();
        this->renderer->positionCamera(world->getObserver()->getCamera());
        this->renderer->translate(rc.translation);
        this->face(rc.rotation);
        this->renderer->renderShape((Shape *) rooms[i]->getModel());
    }
}

void RenderingManagerEngine::renderAllEntities() {
    obj_list ents = world->active_room->models;
    size_t ents_size = ents.size();
    for (size_t i = 0; i < ents_size; i++) {
        Coords c = ents[i]->getCoords();
        this->renderer->resetMatrix();
        this->renderer->positionCamera(world->getObserver()->getCamera());
        this->renderer->translate(c.translation);
        this->face(c.rotation);
        this->renderer->renderShape(ents[i]->getModel());

    }
}

void RenderingManagerEngine::renderAllDecals() {

}

void RenderingManagerEngine::render() {
    
}

void RenderingManagerEngine::positionLights() {
    
}
