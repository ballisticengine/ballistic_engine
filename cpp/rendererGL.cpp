#include "RendererGL.hpp"
#include "types.hpp"
#pragma comment(lib, "glu32.lib") 

void RendererGL::renderVertex(vertex *v,uv *uvs) {
	glNormal3d(v->normal.x,v->normal.y,v->normal.z);
	if(uvs) {
		glTexCoord2d(uvs->u, uvs->v);
	}
	glVertex3d(v->x, v->y, v->z);
}

void RendererGL::begin() {
	glBegin(GL_TRIANGLES); 
}

void RendererGL::beginQuads() {
	glBegin(GL_QUADS);
}

void RendererGL::beginHinted(shape *s) {
	int count=s->getPolyCount();
	glBegin(count_names[count]);
}

void RendererGL::end() {
	glEnd();
}

void RendererGL::setAmbientLight(colorRGB *c) {
	GLfloat global_ambient[] = { c->r, c->g, c->b }; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void RendererGL::renderTerrainSpecific() {
	TerrainMap *tm=w->getTerrain();
	shape *s=tm->getQuads();
	vert_list verts;

	this->assignTexture(w->getTerrain()->getTexture());
	glBegin(GL_QUADS);
	for(int i=0; i<tm->getQuadCount(); i++) {

		verts=s[i].getVertices();

		for(int v=0; v<verts.size(); v++) {
			glVertex3f(verts[v]->x,verts[v]->y,verts[v]->z);
		}

	}
	glEnd();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void RendererGL::lightSpecific(light *l) {
	
	if (light_counter>7) {
	 cout << "Too much lights" << endl;
	 return;
	}

	
	
	coords lc=l->getCoords();
	this->reset();

	this->positionCamera();

	//glRotatef(-90,1,0,0);
	

	this->translate(lc.translation.x,lc.translation.y,lc.translation.z);
	
	//glRotatef(-90,1,0,0);
	GLfloat position[] = { 0, 0, 0, 1.0f };

	//glDisable(GL_LIGHTING);
	if (engineState::getInstance()->debug_visual) {
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D,0);
		glColor3f(1,0,0);
		gluSphere(lightbulb,0.5,10,10);	
		glEnable(GL_LIGHTING);
		glColor3f(1,1,1);
	}
	
	

	glEnable(light_numbers[light_counter]);
	GLfloat ambientLight[] = { 0, 0, 0, 1.0f }; 
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	colorRGBA c=l->getDiffuse();
	GLfloat intensity[]={c.r,c.g,c.b,c.a};
	
	GLfloat shin=30;
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientLight );
	glLightfv(light_numbers[light_counter], GL_AMBIENT, ambientLight); 
	glLightfv(light_numbers[light_counter], GL_DIFFUSE, intensity); 
	glLightfv(light_numbers[light_counter], GL_SPECULAR, intensity);

	glLightfv(light_numbers[light_counter], GL_POSITION, position);

	GLfloat ambient[] = { 1.0f, 0.0f, 0.0f }; 
	
	light_counter++;

}

RendererGL::RendererGL() {
	light_numbers[0]=GL_LIGHT0;
	light_numbers[1]=GL_LIGHT1;
	light_numbers[2]=GL_LIGHT2;
	light_numbers[3]=GL_LIGHT3;
	light_numbers[4]=GL_LIGHT4;
	light_numbers[5]=GL_LIGHT5;
	light_numbers[6]=GL_LIGHT6;
	light_numbers[7]=GL_LIGHT7;
	count_names[3]=GL_TRIANGLES;
	count_names[4]=GL_QUADS;
}



void RendererGL::render() {
	glClearColor(1,1,1,1);
	glClear( GL_DEPTH_BUFFER_BIT );
	light_counter=0;
	glMatrixMode(GL_MODELVIEW);
	/*for(int i=0; i<shaders.size(); i++) {
		glUseProgramObjectARB(shaders[i]);
		//int param=-1;
	//	glGetObjectParameterivARB(shaders[i], GL_OBJECT_LINK_STATUS_ARB, &param);
		//cout << "Shad status" << param << endl;
	}*/
	
	renderSkybox(w->getSkybox());
	this->positionLights();
	this->reset();

	this->positionCamera();

	glFrontFace(GL_CW);

	this->renderAllRooms();

	this->reset();
	this->positionCamera();

	this->renderAllEntities();
	
	glFlush();
	this->flush_callback();
}


/*void RendererGL::renderFaceTexShape(faceTexShape *s) {
	if(s->renderer_hint) {
	 
	}
}*/

void RendererGL::setUpVbos() {
	obj_list models=this->w->getModels();
	GLuint *b;
	float v[3];
	size_t vc;
	for(size_t i=0; i<models.size(); i++) {
		b=new GLuint;
		vc=0;
		glGenBuffers(1,b);
		models[i]->getModel()->renderer_hint=(void *)b;
		glBindBuffer(GL_ARRAY_BUFFER, *b);
		glEnableClientState(GL_VERTEX_ARRAY);
		poly_list ps=models[i]->getModel()->getPolys();
		for(size_t n=0; n<ps.size(); n++) {
			vert_list vs=ps[n]->v;
			for(size_t w=0; w<vs.size(); w++) {
				vs[w]->x;
				v[0]=vs[w]->x;
				v[1]=vs[w]->y;
				v[2]=vs[w]->z;
				glBufferSubData(GL_ARRAY_BUFFER,vc,3,v);
				vc+=3;
			}
		}

	}
}

void RendererGL::specificInit() {
	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
	 cout << "Shaders in place\n";
	}

	glViewport(0, 0,config::getInstance()->getVD()->width, config::getInstance()->getVD()->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);
	gluPerspective(90,1,1,5000);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable( GL_NORMALIZE );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	//glEnable( GL_LIGHTING );
	//glEnable(GL_LIGHT0);
	this->setAmbientLight(&w->getActiveRoom()->ambient_light);
	this->setupTexture(w->getSkybox()->getTexture());

	//this->setupTexture(w->getTerrain()->getTexture());


	lightbulb=gluNewQuadric();   
	bounding_box_q=gluNewQuadric();
	gluQuadricNormals(lightbulb, GLU_SMOOTH);  
	gluQuadricTexture(lightbulb, GL_TRUE);
	gluQuadricNormals(bounding_box_q, GLU_SMOOTH);  
	gluQuadricTexture(bounding_box_q, GL_TRUE);
	ptree & shaders=config::getInstance()->getNode("config.screen.shaders");
	BOOST_FOREACH(const ptree::value_type &shad, shaders) {
		string sn=shad.second.get_value<string>();
		cout << "Adding shader: " << sn << endl;
		addShader(sn);
	}	
	//this->setUpVbos();
}

void RendererGL::addShader(string name) {
 char *vf=loadText(SHADER_DIR+string(DS)+name+".vert"),*ff=loadText(SHADER_DIR+string(DS)+name+".frag");
 const char *vfc=vf,*ffc=ff;
 GLhandleARB vhandle=glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB),
	fhandle=glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
 
 size_t vfs=strlen(vfc),ffs=strlen(ffc);
 GLint * vs=(GLint*)&vfs,* fs=(GLint*)&ffs;
 glShaderSourceARB(vhandle, 1, &vfc,0);
 glShaderSourceARB(fhandle, 1, &ffc,0);
 delete ff; delete vf;
 glCompileShaderARB(vhandle);
 glCompileShaderARB(fhandle);
 GLhandleARB p=glCreateProgramObjectARB();
 glAttachObjectARB(p,vhandle);
	glAttachObjectARB(p,fhandle);
	glLinkProgramARB(p);

	
	shaders.push_back(p);

}

char * RendererGL::loadText(string fn) {
	char *ft;
	FILE *f=fopen(fn.c_str(),"rb");
	fseek(f,0,SEEK_END);
	size_t size=ftell(f);
	fseek(f,0,SEEK_SET);
	ft=new char[size+2];
	
	fread(ft,1,size,f);
	ft[size]=0;
	fclose(f);
	return ft;
}

void RendererGL::renderSkybox(skybox *sky) {
	this->reset();
	glFrontFace(GL_CCW);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	this->translate(0,0,-18);
	this->assignTexture(sky->getTexture());
	glBegin(GL_QUADS);
	this->renderPShape(sky->getShape());

	glEnd();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void RendererGL::assignTexture(texture *t) {
	GLuint tex_id;
	tex_id = this->textures_ids[t];
	glBindTexture(GL_TEXTURE_2D, tex_id);
}

void RendererGL::assignMaterial(Material *m) {
	colorRGBA specular=m->getSpecular(),
		diffuse=m->getDiffuse()
		;
	e_loc shining=m->getShininess(),emit=m->getEmission()
		;

	//cout << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << ", " << diffuse.a << endl;
	 GLfloat diff[]={diffuse.r,diffuse.g,diffuse.b,diffuse.a};
	 GLfloat spec[]={specular.r,specular.g,specular.b,specular.a};
	 GLfloat emi[]={emit,emit,emit,1};
	 glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diff );
	 glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spec );
	 glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shining );
	  glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emi );


}

void RendererGL::setupTexture(texture *t) {

	GLuint tex_id;

	glGenTextures(1, &tex_id);
	this->textures_ids[t] = tex_id;
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexStorage2D(GL_TEXTURE_2D, 8, GL_BGR_EXT, t->getWidth(), t->getHeight());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//for testing
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->getWidth(), t->getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void RendererGL::translateSpecific(e_loc x, e_loc y, e_loc z) {
	glTranslated(x,y,z);
}



void RendererGL::rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d) {
	glRotatef(d,x,y,z);
}

void RendererGL::resetSpecific() {
	glLoadIdentity();
	glTranslatef(0,0,-frustum_start);
}

void RendererGL::positionCameraSpecific() {
	//glRotatef(-90,1,0,0);
}

void RendererGL::drawBoundingBox(BoundingCube *bound) {
	//drawBox(bound->getWidth(),bound->getHeight(),bound->getDepth());
	this->reset();
		this->positionCamera();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDisable(GL_CULL_FACE);
	glColor3f(0,1,0);
	e_loc maxx=bound->max.x,maxy=bound->max.y,maxz=bound->max.z,
			minx=bound->min.x,miny=bound->min.y,minz=bound->min.z;
		;
	glBegin(GL_QUADS);
	  glVertex3d(-minx,-maxy,-maxz);
	  glVertex3d(-maxx,-maxy,-maxz);
	  glVertex3d(-maxx,-miny,-maxz);
	  glVertex3d(-minx,-miny,-maxz);
	  
	  glVertex3d(-minx,-miny,-minz);
	  glVertex3d(-maxx,-miny,-minz);
	  glVertex3d(-maxx,-maxy,-minz);
	  glVertex3d(-minx,-maxy,-minz);

	  glVertex3d(-minx,-miny,-minz);
	  glVertex3d(-minx,-maxy,-minz);
	  glVertex3d(-minx,-maxy,-maxz);
	  glVertex3d(-minx,-miny,-maxz);
	  
	  
		glVertex3d(-maxx,-miny,-maxz);
	  glVertex3d(-maxx,-maxy,-maxz);
		glVertex3d(-maxx,-maxy,-minz);
	  glVertex3d(-maxx,-miny,-minz);
	  

	  glVertex3d(-minx,-miny,-minz);
	  glVertex3d(-minx,-miny,-maxz);
		glVertex3d(-maxx,-miny,-maxz);
	  glVertex3d(-maxx,-miny,-minz);

	  
	  glVertex3d(-maxx,-maxy,-minz);
	  glVertex3d(-maxx,-maxy,-maxz);
	  glVertex3d(-minx,-maxy,-maxz);
	  glVertex3d(-minx,-maxy,-minz);
	
	  glEnd();
	  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	  glEnable(GL_TEXTURE_2D);
	  glEnable(GL_LIGHTING);
	  	glEnable(GL_CULL_FACE);
		glColor3f(1,1,1);
}

void RendererGL::drawBox(e_loc width,e_loc height,e_loc depth) {
	e_loc xx=width/2,yy=height/2,zz=depth/2;
	
	
	
	
}