#include "resources/WorldLoader.hpp"

ResourceType WorldLoader::getType() {
    return LEVEL;
}

extensions_s WorldLoader::getFileExtensions() {
    extensions_s exts;
    return exts;
}

bool WorldLoader::save(World *world, string file_name) {
    return false;
}