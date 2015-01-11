#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "factories/factory.hpp"
#include "types/texture.hpp"
#include "loaders/texLoader.hpp"

class textureFactory : public factory, public singleton<textureFactory> {
protected:
    virtual void * actualLoad(string fn);
    virtual string getSubDir();
    texLoader *loader;
public:
    textureFactory();

};

#endif