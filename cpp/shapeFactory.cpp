#include "shapeFactory.hpp"

void * shapeFactory::actualLoad(string fn) {
  string ext=factory::getExt(fn);
  shape *s=new shape();
  if(ext==MD2_EXT) {
  loaderMD2 *loader=loaderMD2::getInstance();
  
  loader->loadMD2(fn,s,this->scale);
  //this->scale=1; //skalowanie jest jednorazowe
  cout << "SSS: " << s->getTris().size() << ", " << fn << endl;
  } 
  else if(ext==GEOM_MEM_EXT) {
	 loaderXML *loader=loaderXML::getInstance();
	loader->loadXML(*shp,s);
	return (void *)s;
  }
  else {
   cout << "Unknown extension " << ext << endl;
   return 0;
  }
  return (void *)s;
}

void shapeFactory::setScale(e_loc scale) {
 this->scale=scale;
}

shapeFactory::shapeFactory() {
 scale=1;
}

XMLShapeInfo shapeFactory::getXML(ptree &shp) {
	loaderXML *loader=loaderXML::getInstance();
	string name=loader->getName(shp);
	this->shp=&shp;
	name=name+"."+GEOM_MEM_EXT;
	XMLShapeInfo xmlsi;
	xmlsi.s=(shape *)this->get(name);
	xmlsi.tex_fn=loader->getTexFN(shp);
	return xmlsi;
}