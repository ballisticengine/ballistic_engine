#include "python/ScriptBase.hpp"
#include "misc/utils.hpp"

ScriptBase::ScriptBase(string filename) {
    this->filename = boost::filesystem::basename(filename);
    code = Utils::loadText(filename);
}

const char  * const ScriptBase::getCode() {
    return this->code;
}

ScriptBase::~ScriptBase() {
    delete code;
}