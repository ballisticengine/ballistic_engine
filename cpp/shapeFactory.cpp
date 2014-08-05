#include "shapeFactory.hpp"

void * shapeFactory::actualLoad(string fn) {
  shape *s=new shape();
  loaderMD2 *loader=loaderMD2::getInstance();
  
  loader->loadMD2(fn,s);
  cout << "SSS: " << s->getTris().size() << ", " << fn << endl;
  return (void *)s;
}