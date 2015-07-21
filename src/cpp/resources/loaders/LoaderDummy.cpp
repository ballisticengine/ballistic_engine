#include "resources/loaders/LoaderDummy.hpp"

extensions_s LoaderDummy::getFileExtensions() {
    extensions_s exts;
    exts.insert("txt");
    return exts;
}

void * LoaderDummy::load(string file_name) {
    FILE *f;
    f = fopen(file_name.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *file_contents=new char[size];
    fread(file_contents, 1, size, f);
    return file_contents;
}

ResourceType LoaderDummy::getType() {
    return OTHER;
}

extern "C" {

    Loader * returnLoader() {
        return (Loader *) new LoaderDummy();
    }
}