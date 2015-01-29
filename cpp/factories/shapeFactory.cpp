#include "factories/shapeFactory.hpp"

void shapeFactory::setAnimator(ModelAnimator *a) {
    this->animator = a;
}

ModelAnimator * shapeFactory::getAnimator() {
    return this->animator;
}

void * shapeFactory::actualLoad(string fn) {
    string ext = Utils::getExt(fn);
    modelInfo *mi = new modelInfo;
    mi->s = new shape();
    int cw = GL_CW;
    mi->s->renderer_hint = (void *) new int;
    *((int *) mi->s->renderer_hint) = cw;
    if (ext == MD2_EXT) {
        loaderMD2 *loader = loaderMD2::getInstance();

        loader->loadMD2(fn, mi->s, this->scale);
        //this->scale=1; //skalowanie jest jednorazowe
    } else if (ext == XML_EXT) {
        loaderXML *loader = loaderXML::getInstance();

        loader->load(fn, mi, uses_common);
    } else if (ext == GEOM_MEM_EXT) {
        cout << "GEOM";
        loaderXML *loader = loaderXML::getInstance();
        //write_xml(std::cout, *shp);
        loader->loadXML(*shp, mi->s);
        return (void *) mi->s;
    } else {
        cout << "Unknown extension " << ext << endl;
        return 0;
    }
    return (void *) mi->s;
}

void shapeFactory::setScale(e_loc scale) {
    this->scale = scale;
}

shapeFactory::shapeFactory() {
    scale = 1;
}

string shapeFactory::getSubDir() {
    return string("models");
}

shape * shapeFactory::getXML(ptree shp) {
    loaderXML *loader = loaderXML::getInstance();

    string name = loader->getName(shp);

    this->shp = &shp;
    name = name + "." + GEOM_MEM_EXT;

    shape *s = (shape *)this->get(name);

    return s;
}