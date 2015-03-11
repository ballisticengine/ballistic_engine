#include "libload/LibLoad.hpp"

RendererAbstract * LibLoad::getRenderer(string name) {
    lib_handle h=this->load(name);
    typedef void* (*hello_t)();;
    hello_t fn;
    cout << dlerror() << endl;
    fn=( hello_t)dlsym(h, "returnRenderer");
    cout << dlerror() << endl;
//    RendererAbstract *(*rf)()=(RendererAbstract *())vf;
    cout << fn << ", " << h << endl;
    return (RendererAbstract *)fn();
}

lib_handle LibLoad::load(string fn) {
    lib_handle h= dlopen(fn.c_str(), RTLD_NOW  | RTLD_GLOBAL);
}

LibLoad::~LibLoad() {
    for(size_t i=0; i<libs.size(); i++) {
         dlclose(libs[i]);
    }
}