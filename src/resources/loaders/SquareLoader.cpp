#include "resources/loaders/SquareLoader.hpp"

extensions_s SquareLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void *SquareLoader::load(string level_name) {
    
}


ResourceType SquareLoader::getType() {
    return SHAPE;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new SquareLoader();
    }
}