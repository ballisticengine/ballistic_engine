#include "resources/WorldLoader.hpp"

ResourceType WorldLoader::getType() {
    return LEVEL;
}

extensions_s WorldLoader::getFileExtensions() {
    extensions_s exts;
    return exts;
}