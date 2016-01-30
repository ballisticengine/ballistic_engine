#include "resources/loaders/SquareLoader.hpp"
#include "misc/utils.hpp"
#include "types/types.hpp"
#include "types/shape.hpp"

#include <cstdio>

extensions_s SquareLoader::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void *SquareLoader::load(string file_name) {
    char *contents = Utils::loadText(file_name);
    if (!contents) {
        return 0;
    }

    Shape *s = new Shape();
    cout << "Contents" << contents << endl;
    return s;
}

ResourceType SquareLoader::getType() {
    return SHAPE;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new SquareLoader();
    }
}