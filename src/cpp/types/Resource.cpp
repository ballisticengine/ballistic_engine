#include "types/Resource.hpp"

string Resource::getFilename() {
    return this->filename;
}

string Resource::getOrigFilename() {
    return this->orig_filename;

}

void Resource::setFilename(string fn) {
    this->filename = fn;
}

void Resource::setOrigFilename(string fn) {
    this->orig_filename = fn;
}