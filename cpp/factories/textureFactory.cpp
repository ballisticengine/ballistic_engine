#include "factories/textureFactory.hpp"

void * TextureFactory::actualLoad(string fn) {
 Texture *t=new Texture(fn);
// t->load();
   loader->load(fn,t); 
 return (void *)t;
}

string TextureFactory::getSubDir() {
    return string("textures");
}

TextureFactory::TextureFactory() {
    loader=TexLoader::getInstance();
}