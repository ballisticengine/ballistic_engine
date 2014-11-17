#include "loaderXML.hpp"

void loaderXML::toShape(ptree &geom,faceTexShape *s) {
  texPoly *vt;
  
  BOOST_FOREACH(const ptree::value_type &f, geom) {
   //cout << "FACE" << endl;
    vert_list vs_tmp;
	int i=0;
	ptree verts=f.second.get_child("vertices");
   BOOST_FOREACH(const ptree::value_type &vx, verts) {
	  //cout << " VERTEX" << endl;
	   e_loc 
		   x=vx.second.get<e_loc>("x")
		   ,y=vx.second.get<e_loc>("y")
		   ,z=vx.second.get<e_loc>("z")
		   ,u=vx.second.get<e_loc>("u")
		   ,v=vx.second.get<e_loc>("v");
	   //cout << x << " " << y << " " << z << " " << u << " " << v << endl; 
	   vs_tmp.push_back(new vertex(x,y,z, u, v));
	   i++;
   }
   texture *t=(texture *)textureFactory::getInstance()->get(f.second.get<string>("texture"));
   vt = new texPoly(vs_tmp);
   Material * mt=new Material();
   mt->setTexture(t);
   vt->setMaterial(mt);   
   s->addPoly(vt);
  }
  
 }

 string loaderXML::loadXML(ptree &tree,faceTexShape *s) {
	 ptree & geom=tree.get_child("shape.geom");

	 string name=this->getName(tree);
	 this->toShape(geom,s);
	 return name;
 }

 string loaderXML::getName(ptree &tree) {
	 string name=tree.get<string>("shape.name");
	 return name;
 }

