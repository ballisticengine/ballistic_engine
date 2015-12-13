#include "world/WorldManager.hpp"
#include "resources/WorldLoader.hpp"
#include "libload/LibLoad.hpp"

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

bool WorldManager::saveInto(string file_name) {
     WorldLoader *world_loader = (WorldLoader *) LibLoad::getInstance()->getLoaderByExtension("xml", LEVEL);
     world_loader->save(this->world, file_name, "geometry.xml");
 }

WorldManager::WorldManager() {

}

WorldManager::~WorldManager() {

}

 