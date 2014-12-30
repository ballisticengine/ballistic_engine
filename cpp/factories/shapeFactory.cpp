#include "factories/shapeFactory.hpp"

void shapeFactory::setAnimator(ModelAnimator *a) {
	this->animator=a;
}

ModelAnimator * shapeFactory::getAnimator() {
	return this->animator;
}

void * shapeFactory::actualLoad(string fn) {
  string ext=factory::getExt(fn);
  faceTexShape *s=new faceTexShape();
  if(ext==MD2_EXT) {
  loaderMD2 *loader=loaderMD2::getInstance();
  
  loader->loadMD2(fn,s,this->scale);
  //this->scale=1; //skalowanie jest jednorazowe
  } else if (ext==XML_EXT) {
	 loaderXML *loader=loaderXML::getInstance();
	 loader->load(fn,s);
	
	 
  }
  else if(ext==GEOM_MEM_EXT) {
	 cout << "GEOM";
	  loaderXML *loader=loaderXML::getInstance();
		//write_xml(std::cout, *shp);
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

string shapeFactory::getSubDir() {
    return string("models");
}


faceTexShape * shapeFactory::getXML(ptree shp) {
	loaderXML *loader=loaderXML::getInstance();
	
	string name=loader->getName(shp);
	
	this->shp=&shp;
	name=name+"."+GEOM_MEM_EXT;
	
	faceTexShape *s=(faceTexShape *)this->get(name);
	
	return s;
}