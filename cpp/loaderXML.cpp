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

	ptree 
		verts=geom.get_child("vertices"),
		faces=geom.get_child("faces"),
		uvs=geom.get_child("uvs")
		;
	size_t
		v_count=geom.get<size_t>("counts.vertices"),
		f_count=geom.get<size_t>("counts.faces"),
		uv_count=geom.get<size_t>("counts.uvs"),
		vpf=geom.get<size_t>("counts.v_p_f")
		;
	s->f_count=f_count;
	s->v_count=v_count;
	s->v_per_poly=vpf;
	s->uv_count=uv_count;
	s->vertices=new v_type[v_count];
	s->normals=new n_type[v_count];
	s->faces=new size_t*[f_count];
	s->uvs=new uv[uv_count];
	s->textures=new texture*[f_count];
	int i;
	
	i=0;
	BOOST_FOREACH(const ptree::value_type &vx,verts) {
		ptree 
			coords=vx.second.get_child("coords"),
			normal=vx.second.get_child("normal")
			;
		e_loc 
			x=coords.get<e_loc>("x"),
			y=coords.get<e_loc>("y"),
			z=coords.get<e_loc>("z"),
			nx=normal.get<e_loc>("x"),
			ny=normal.get<e_loc>("y"),
			nz=normal.get<e_loc>("z")
			;
		s->vertices[i].x=x;
		s->vertices[i].y=y;
		s->vertices[i].z=z;
		s->normals[i].x=nx;
		s->normals[i].y=ny;
		s->normals[i].z=nz;
		
		MathTypes::vector norm;
		
		i++;
	} 

	/*i=0;
	BOOST_FOREACH(const ptree::value_type &uv,uvs) {
		s->uvs[i].u=uv.second.get<e_loc>("u");
		s->uvs[i].u=uv.second.get<e_loc>("v");
		i++;
	}*/
	
	i=0;

	int n=0,uvc=0;
	BOOST_FOREACH(const ptree::value_type &face,faces) {
		ptree f_verts=face.second.get_child("vertices");
		s->faces[i]=new size_t[vpf];
		try {
			
		string texname=face.second.get<string>("texture");
				texture *t=(texture *)textureFactory::getInstance()->get(texname);
				s->textures[i]=t;
				cout << texname << endl;
			} catch(std::exception e) {
				s->textures[i]=0;
			} 
		n=0;
		BOOST_FOREACH(const ptree::value_type &f_vx,f_verts) {
			size_t index=f_vx.second.get<size_t>("i");
			s->faces[i][n]=index;
			ptree uv=f_vx.second.get_child("uv");
			s->uvs[uvc].u=uv.get<e_loc>("u");
			s->uvs[uvc].v=uv.get<e_loc>("v");
			uvc++;
			n++;

		}
		i++;
	}
	/*BOOST_FOREACH(const ptree::value_type &f, geom) {
		cout << "FACE" << endl;
		vert_list vs_tmp;
		uv_list uv_tmp;
		int i=0;
		ptree verts=f.second.get_child("vertices");
		BOOST_FOREACH(const ptree::value_type &vx, verts) {
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

