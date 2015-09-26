#include "resources/Loader.hpp"

bool Loader::handlesEntension(string extension) {
    extensions_s exts = this->getFileExtensions();
    if (exts.find(extension) != exts.end()) {
        return true;
    }
    return false;
}

void Loader::addDependency(string file_name, void **target, ResourceType type) {
    LoaderDependency dep;
    dep.file_name = file_name;
    dep.target = target;
    dep.type = type;
    dependencies.push_back(dep);
}

dep_list Loader::getDependencies() {
    return this->dependencies;
}

void Loader::cleanDependencies() {
    this->dependencies.clear();
}

void *Loader::loadFromData(void *data, size_t size) {
    
}

size_t Loader::getPriority() {
    return 0;
}