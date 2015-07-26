#include "renderer/RenderingManager.hpp"

void RenderingManager::setFlush(flush_function flush_callback) {
    this->flush_callback = flush_callback;
}

void RenderingManager::init() {

}

void RenderingManager::setupTextures() {
     vector<LoadedResource *> ts = ResourceManager::getInstance()->getByType(TEXTURE);

    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) {
        
        if (ts[i]->object) {
            this->renderer->setupTexture((Texture *) ts[i]->object);
        }
    }
}

void RenderingManager::face(Vector3d &v) {
    this->renderer->rotate(Vector3d(1, 0, 0), v.x);
    this->renderer->rotate(Vector3d(0, 1, 0), v.y);
    this->renderer->rotate(Vector3d(0, 0, 1), v.z);
}

void RenderingManager::renderAllRooms() {
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

void RenderingManager::renderAllEntities() {
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

void RenderingManager::renderAllDecals() {

}

void RenderingManager::render() {
    this->renderer->beforeFrame();
    this->renderer->resetMatrix();
    this->renderer->positionCamera(world->getObserver()->getCamera());
   this->renderAllRooms();
    //this->renderAllDecals();
    this->renderer->resetMatrix();
    this->renderer->positionCamera(world->getObserver()->getCamera());
   // this->renderAllEntities();
    this->renderer->afterFrame();
    this->flush_callback();
}

RenderingManager::RenderingManager() {
    this->world = World::getInstance();
}

RenderingManager::~RenderingManager() {

}

void RenderingManager::setRenderer(RendererInterface *renderer) {
    this->renderer = renderer;
}

RendererInterface * RenderingManager::getRenderer() {
    return this->renderer;
}