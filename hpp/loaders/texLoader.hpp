#ifndef TEXLOADER_HPP
#define	TEXLOADER_HPP

#include <string>

using namespace std;

#include "misc/singleton.hpp"

class texLoader : public singleton<texLoader> {
    public:
    bool load(string fn);
};

#endif	

