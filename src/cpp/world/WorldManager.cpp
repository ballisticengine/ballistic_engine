#include "world/WorldManager.hpp"

World *WorldManager::getCurrentWorld() {
    return this->world;
}

void WorldManager::setWorld(World *w) {
    this->world = w;
}

WorldManager::WorldManager() {
    
}

WorldManager::~WorldManager() {
    
}
