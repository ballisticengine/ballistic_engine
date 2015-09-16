#include "ui/UISignalData.hpp"

void UISignalData::set(string k, string v) {
    sigmap[k] = v;
}

string UISignalData::get(string k) {
    return sigmap[k];
}