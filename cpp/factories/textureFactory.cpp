#include "factories/textureFactory.hpp"

void * TextureFactory::actualLoad(string fn) {
 Texture *t=new Texture(fn);
// t->load();
 if (!loader->load(fn,t)) {
     Factory::abort("File "+fn);
 }
 
 return (void *)t;
}

string TextureFactory::getSubDir() {
    return string("textures");
}

TextureFactory::TextureFactory() {
    loader=TexLoader::getInstance();
}