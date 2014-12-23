#include "loaderXML.hpp"

bool loaderXML::load(string fn, faceTexShape *s) {

	ptree pt;
	read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
	ptree shp=pt.get_child("shape");
	ptree geom=shp.get_child("geom");
	this->toShape(geom,s);
	return true;
}

void loaderXML::toShape(ptree &geom,faceTexShape *s) {
	texPoly *vt;
	ptree 
		verts=geom.get_child("vertices"),
		faces=geom.get_child("faces")
		;
	//write_xml(std::cout,verts);
	BOOST_FOREACH(const ptree::value_type &vx,verts) {
		//write_xml(std::cout,vx.second);
		ptree 
			coords=vx.second.get_child("coords"),
			normal=vx.second.get_child("normal")
			;
		
		
	} 

	/*BOOST_FOREACH(const ptree::value_type &f, geom) {
		cout << "FACE" << endl;
		vert_list vs_tmp;
		uv_list uv_tmp;
		int i=0;
		ptree verts=f.second.get_child("vertices");
		cout << "vSSS";
		BOOST_FOREACH(const ptree::value_type &vx, verts) {
			cout << " VERTEX" << endl;
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
		
		vt = new texPoly(vs_tmp);
		
		try {
			Material * mt=new Material();
			ptree matx=f.second.get_child("material");
			colorRGBA sc,dc;
			sc.r=matx.get<float>("specular.r");
			sc.g=matx.get<float>("specular.g");
			sc.b=matx.get<float>("specular.b");
			dc.r=matx.get<float>("diffuse.r");
			dc.g=matx.get<float>("diffuse.g");
			dc.b=matx.get<float>("diffuse.b");
			e_loc emission=matx.get<float>("emit");
			e_loc shining=matx.get<float>("shining");
			mt->setSpecular(sc);
			mt->setDiffuse(dc);
			mt->setShininess(shining);
			mt->setEmission(emission);

			vt->setMaterial(mt);
		}catch(std::exception e) {
			
			vt->setMaterial(0);
		}
		
		try {
			string texname=f.second.get<string>("texture");
			texture *t=(texture *)textureFactory::getInstance()->get(texname);
			vt->setTexture(t);
		} catch(std::exception e) {
			vt->setTexture(0);
		} 
		vt->uvs=uv_tmp;
		s->addPoly(vt);
	}*/

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

