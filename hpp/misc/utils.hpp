#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

namespace Utils {

char *loadText(string fn);

string getExt(string fn);

#define deleteVector(v) for(size_t i=0; i<v.size(); i++) {delete v[i];}


};
#endif