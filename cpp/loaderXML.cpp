#include "loaderXML.hpp"

void loaderXML::toShape(ptree &geom,faceTexShape *s) {
  texPoly *vt;
  
  BOOST_FOREACH(const ptree::value_type &f, geom) {
   //cout << "FACE" << endl;
    vert_list vs_tmp;
	uv_list uv_tmp;
	int i=0;
	ptree verts=f.second.get_child("vertices");
   BOOST_FOREACH(const ptree::value_type &vx, verts) {
	  //cout << " VERTEX" << endl;
	   e_loc 
		   x=vx.second.get<e_loc>("x")
		   ,y=vx.second.get<e_loc>("y")
		   ,z=vx.second.get<e_loc>("z")
		   ,u=vx.second.get<e_loc>("u")
		   ,v=vx.second.get<e_loc>("v")
			,nx=vx.second.get<e_loc>("nx")
			,ny=vx.second.get<e_loc>("ny")
			,nz=vx.second.get<e_loc>("nz")
			;
	   //cout << x << " " << y << " " << z << " " << u << " " << v << endl; 
	   vertex *vv=new vertex(x,y,z);
	   MathTypes::vector norm;
	   norm.x=nx;
	   norm.y=ny;
	   norm.z=nz;
		vv->normal=norm;
	   vs_tmp.push_back(vv);
	   uv_tmp.push_back(new uv(u,v));
	   
	   i++;
   }
   Material * mt=new Material();
    vt = new texPoly(vs_tmp);
   try {
   string texname=f.second.get<string>("texture");
   texture *t=(texture *)textureFactory::getInstance()->get(texname);
  
   
	mt->setTexture(t);
   
	vt->setTexture(t);
	vt->setMaterial(mt);
   } catch(std::exception e) {
	   vt->setTexture(0);
	   vt->setMaterial(0);
   } 
	vt->uvs=uv_tmp;
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

