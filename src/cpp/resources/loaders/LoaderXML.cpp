#include "resources/loaders/LoaderXML.hpp"

extensions_s LoaderXML::getFileExtensions() {
    extensions_s exts;
    exts.insert("xml");
    return exts;
}

LoaderType LoaderXML::getType() {
    return SHAPE;
}

void *LoaderXML::load(string file_name) {
    return 0;

}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new LoaderXML();
    }
}