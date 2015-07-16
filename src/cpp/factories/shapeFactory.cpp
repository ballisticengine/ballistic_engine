#include "factories/shapeFactory.hpp"

void ShapeFactory::setAnimator(ModelAnimator *a) {
    this->animator = a;
}

ModelAnimator * ShapeFactory::getAnimator() {
    return this->animator;
}

LoadedResource * ShapeFactory::actualLoad(string fn, string orig_fn) {
    string ext = Utils::getExt(fn);
    ModelInfo *mi = new ModelInfo;
    mi->s = new Shape();
    int cw = GL_CW;
    mi->s->renderer_hint = (void *) new int;
    
    *((int *) mi->s->renderer_hint) = cw;
    if (ext == MD2_EXT) {
        LoaderMD2 *loader = LoaderMD2::getInstance();

        loader->loadMD2(fn, mi->s, this->scale);
        //this->scale=1; //skalowanie jest jednorazowe
    } else if (ext == XML_EXT) {
        LoaderXML *loader = LoaderXML::getInstance();

        loader->load(fn, mi, uses_common);
    } else if (ext == GEOM_MEM_EXT) {
        cout << "GEOM";
        LoaderXML *loader = LoaderXML::getInstance();
        //write_xml(std::cout, *shp);
        loader->loadXML(*shp, mi->s);
        return new LoadedResource((void *) mi->s, (Resource *)mi->s);
    } else {
        cout << "Unknown extension " << ext << endl;
        return 0;
    }
    
    return new LoadedResource((void *) mi, (Resource *)mi->s);
}

Shape * ShapeFactory::getShape(string fn,bool force_common) {
    ModelInfo *mi=(ModelInfo *)this->get(fn,force_common);
    return mi->s;
}

void ShapeFactory::setScale(e_loc scale) {
    this->scale = scale;
}

ShapeFactory::ShapeFactory() {
    scale = 1;
}

string ShapeFactory::getSubDir() {
    return string("models");
}

Shape * ShapeFactory::getXML(ptree shp) {
    LoaderXML *loader = LoaderXML::getInstance();

    string name = loader->getName(shp);

    this->shp = &shp;
    name = name + "." + GEOM_MEM_EXT;

    Shape *s = (Shape *)this->get(name);

    return s;
}