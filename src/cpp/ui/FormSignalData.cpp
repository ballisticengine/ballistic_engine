#include "ui/FormSignalData.hpp"

void FormSignalData::set(string k, string v) {
    sigmap[k] = v;
}

string FormSignalData::get(string k) {
    return sigmap[k];
}