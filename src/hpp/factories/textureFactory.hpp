#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "factories/factory.hpp"
#include "types/texture.hpp"
#include "loaders/texLoader.hpp"

class TextureFactory : public Factory, public Singleton<TextureFactory> {
protected:
    virtual void * actualLoad(string fn, string orig_fn);
    virtual string getSubDir();
    TexLoader *loader;
public:
    TextureFactory();

};

#endif