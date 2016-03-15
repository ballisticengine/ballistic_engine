#include "renderer/RenderingManager.hpp"
#include "world/WorldManager.hpp"

#include "renderer/actions/RenderAllRooms.hpp"
#include "renderer/actions/RenderAllEntities.hpp"
#include "renderer/actions/RenderSkybox.hpp"
#include "renderer/actions/PositionLights.hpp"
#include "renderer/actions/RenderUI.hpp"


void RenderingManager::render() {
    this->renderer->beforeFrame();

    for(auto a: actions) {
        a->render();
    }
    
    this->renderer->afterFrame();
    this->flush_callback();
}

RenderingManager::RenderingManager() {
    
    this->world = WorldManager::getInstance()->getCurrentWorld();
    if (!this->world) {
        return;
    }
    
    addAction(new PositionLights());
    addAction(new RenderSkybox());
    addAction(new RenderAllRooms());
    addAction(new RenderAllEntities());
    addAction(new RenderUI());
    
    
    for(auto a: this->actions) {
        a->setWorld(world);
    }
}

RenderingManager::~RenderingManager() {

}

void RenderingManager::setupTextures() {
    this->renderer->addShader("light");
    vector<LoadedResource *> ts = ResourceManager::getInstance()->getByType(TEXTURE);

    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) {

        if (ts[i]->object) {
            this->renderer->setupTexture((Ballistic::Types::Texture *) ts[i]->object);
        }
    }
}
