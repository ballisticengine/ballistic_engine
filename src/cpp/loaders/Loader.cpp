#include "loaders/Loader.hpp"

bool Loader::handlesEntension(string extension) {
    extensions_s exts = this->getFileExtensions();
    if (exts.find(extension) != exts.end()) {
        return true;
    }
    return false;
}

