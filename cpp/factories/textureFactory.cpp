#include "factories/textureFactory.hpp"

void * textureFactory::actualLoad(string fn) {
 texture *t=new texture(fn);
 t->load();
 return (void *)t;
}

string textureFactory::getSubDir() {
    return string("textures");
}

textureFactory::textureFactory() {
    
}