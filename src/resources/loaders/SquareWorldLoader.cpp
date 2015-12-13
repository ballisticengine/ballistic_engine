#include "resources/loaders/SquareWorldLoader.hpp"

extensions_s SquareWorldLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void *SquareWorldLoader::load(string level_name) {

}