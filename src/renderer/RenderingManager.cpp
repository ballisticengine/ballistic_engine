#include "renderer/RenderingManager.hpp"
#include "world/WorldManager.hpp"




void RenderingManager::positionLights() {
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

void RenderingManager::render() {
    this->renderer->beforeFrame();
    this->positionLights();
    this->renderer->renderSkybox(world->sky);
    this->renderer->resetMatrix();
    this->renderer->positionCamera(world->getObserver()->getCamera());
    this->renderAllRooms();
    this->renderer->resetMatrix();
    this->renderer->positionCamera(world->getObserver()->getCamera());
    this->renderAllEntities();
    this->renderer->resetMatrix();
    //tutaj translate to frustum.left i powinno być ok tylko w rmsdl2 coś poprawic
//    this->renderer->translate(
//            Vector3d(this->renderer->getFrustum().left,
//            this->renderer->getFrustum().top,
//           0
//            )
//            );
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();
    this->renderer->afterFrame();
    this->flush_callback();
}

RenderingManager::RenderingManager() {
    
    this->world = WorldManager::getInstance()->getCurrentWorld();
    if (!this->world) {
        return;
    }
    if (world->sky) {
        world->sky->makeShape(20, 20); //TODO: move this to world loader
    }
}

RenderingManager::~RenderingManager() {

}

