#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "factory.hpp"

class textureFactory : public factory<texture> {
protected:
		texture * actualLoad(string fn) {
		}
};

#endif