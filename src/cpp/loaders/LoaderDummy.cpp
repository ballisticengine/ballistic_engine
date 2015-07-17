#include "loaders/LoaderDummy.hpp"

extensions_s LoaderDummy::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void * LoaderDummy::load(string file_name) {
    return 0;
}

LoaderType LoaderDummy::getType() {
    return OTHER;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new LoaderDummy();
    }
}