#include "shapeFactory.hpp"

void * shapeFactory::actualLoad(string fn) {
  shape *s=new shape();
  loaderMD2 *loader=loaderMD2::getInstance();
  
  loader->loadMD2(fn,s,this->scale);
  //this->scale=1; //skalowanie jest jednorazowe
  cout << "SSS: " << s->getTris().size() << ", " << fn << endl;
  return (void *)s;
}

void shapeFactory::setScale(e_loc scale) {
 this->scale=scale;
}

shapeFactory::shapeFactory() {
 scale=1;
}