#include "world/WorldManager.hpp"

World *WorldManager::getCurrentWorld() {
    if (this->world) {
        return this->world;
    } else {
        return 0;
    }
}

void WorldManager::setWorld(World *w) {
    this->world = w;
}

WorldManager::WorldManager() {

}

WorldManager::~WorldManager() {

}
