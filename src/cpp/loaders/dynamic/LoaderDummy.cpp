#include "loaders/dynamic/LoaderDummy.hpp"

extensions_s LoaderDummy::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void * LoaderDummy::load(string file_name) {
    return 0;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new LoaderDummy();
    }
}