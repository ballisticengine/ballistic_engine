#include "factories/shapeFactory.hpp"

void shapeFactory::setAnimator(ModelAnimator *a) {
    this->animator = a;
}

ModelAnimator * shapeFactory::getAnimator() {
    return this->animator;
}

void * shapeFactory::get(string fn, bool force_common,bool clone) {
    this->force_common = force_common;

    
    
    if (items.find(fn) == items.end() || clone) {
        string path;

        if (fn[0] == '@' || force_common) {
            uses_common = true;
            string rfn;
            if (fn[0] == '@') {
                rfn = fn.substr(1, fn.size());
            } else {
                rfn = fn;
            }
            path = wd + DS + string(COMMON_DIR) + DS + getSubDir() + DS + rfn;
        } else {
            path = wd + DS + string(LVL_DIR) + DS + lvl + DS + getSubDir() + DS + fn;
            uses_common = false;
        }
        
        return this->actualLoad(path);
        //cout << "Factory: " << path << endl;
        //cout.flush();
//        if(clone) {
//            void *p=this->actualLoad(path);
//            item_ptr.push_back(p);
//        } else {
//            items[fn] = this->actualLoad(path);
//            item_ptr.push_back(items[fn]);
//        }
    }
    return items[fn];
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
    return (void *) mi;
}

shape * shapeFactory::getShape(string fn,bool force_common) {
    modelInfo *mi=(modelInfo *)this->get(fn,force_common);
    return mi->s;
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