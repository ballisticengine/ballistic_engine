#include "factories/textureFactory.hpp"

void * textureFactory::actualLoad(string fn) {
 texture *t=new texture();
// t->load();
   loader->load(fn,t); 
 return (void *)t;
}

string textureFactory::getSubDir() {
    return string("textures");
}

textureFactory::textureFactory() {
    loader=texLoader::getInstance();
}