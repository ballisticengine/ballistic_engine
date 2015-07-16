#include "factories/textureFactory.hpp"

LoadedResource * TextureFactory::actualLoad(string fn, string orig_fn) {
 Texture *t=new Texture(fn, orig_fn);
// t->load();
 if (!loader->load(fn,t)) {
     Factory::abort("File "+fn);
 }
 LoadedResource *res=new LoadedResource((void *)t, (Resource *)t);
 return res;
}

string TextureFactory::getSubDir() {
    return string("textures");
}

TextureFactory::TextureFactory() {
    loader=TexLoader::getInstance();
}