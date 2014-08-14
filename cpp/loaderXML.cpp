#include "loaderXML.hpp"

void loaderXML::toShape(ptree &geom,faceTexShape *s) {
 
  triangle *vt;
  BOOST_FOREACH(const ptree::value_type &f, geom) {
   //cout << "FACE" << endl;
    vertex * vs_tmp[3];
	int i=0;
   BOOST_FOREACH(const ptree::value_type &vx, (ptree&)f.second) {
	 //  cout << vx.first.c_str() << endl;
	   e_loc 
		   x=vx.second.get<e_loc>("x")
		   ,y=vx.second.get<e_loc>("y")
		   ,z=vx.second.get<e_loc>("z")
		   ,u=vx.second.get<e_loc>("u")
		   ,v=vx.second.get<e_loc>("v");
	    vs_tmp[i] = new vertex(x,y,z, u, v);
	   i++;
   }
   vt = new texTriangle(vs_tmp[0], vs_tmp[1], vs_tmp[2]);
        s->addTriangle(vt);
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

