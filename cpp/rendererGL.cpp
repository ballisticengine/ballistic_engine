#include "rendererGL.hpp"
#include "types.hpp"
#pragma comment(lib, "glu32.lib") 

void rendererGL::renderVertex(vertex *v) {
	glTexCoord2d(v->u, v->v);
	glNormal3d(v->normal.x,v->normal.y,v->normal.z);
	glVertex3d(v->x, v->y, v->z);
}

void rendererGL::begin() {
	glBegin(GL_TRIANGLES); 
}

void rendererGL::beginQuads() {
	glBegin(GL_QUADS);
}

void rendererGL::end() {
	glEnd();
}

void rendererGL::renderTerrainSpecific() {
	TerrainMap *tm=w->getTerrain();
	shape *s=tm->getQuads();
	vert_list verts;
	//cout << "QC " << tm->getQuadCount() << endl;
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	this->assignTexture(w->getTerrain()->getTexture());
	glBegin(GL_QUADS);
	for(int i=0; i<tm->getQuadCount(); i++) {

		verts=s[i].getVertices();
		//cout << "VS " << verts.size() << endl;
		for(int v=0; v<verts.size(); v++) {
			glVertex3f(verts[v]->x,verts[v]->y,verts[v]->z);
		}

	}
	glEnd();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void rendererGL::lightSpecific(light *l) {
	//return;
	coords c=l->getCoords();
	this->reset();

	this->positionCamera();

	//this->translate(c.x,c.y,c.z);
	
	//glRotatef(-90,1,0,0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	this->translate(c.x,c.y,c.z);
	glRotatef(-90,1,0,0);
	GLfloat position[] = { 0, 0, 0, 1.0f };
	//gluSphere(lightbulb,4,10,10);

	GLfloat ambientLight[] = { 0, 0, 0, 1.0f }; 
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat[]= {0.6, 0.6, 0.6, 1.0};
	GLfloat shin=30;
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientLight );
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);  
	glEnable(GL_COLOR_MATERIAL)        ;
   
	glColor3f(1,1,0);
	GLfloat ambient[] = { 1.0f, 0.0f, 0.0f }; 
	// glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	
	
	
	
	

}

rendererGL::rendererGL() {

}



void rendererGL::render() {

	glClear( GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	for(int i=0; i<shaders.size(); i++) {
		glUseProgramObjectARB(shaders[i]);
		//int param=-1;
	//	glGetObjectParameterivARB(shaders[i], GL_OBJECT_LINK_STATUS_ARB, &param);
		//cout << "Shad status" << param << endl;
	}
	glColor3f(1,1,1);
	renderSkybox(w->getSkybox());
	this->positionLights();
	this->reset();

	this->positionCamera();


	glRotatef(-90,1,0,0);


	glFrontFace(GL_CW);

	this->renderAllRooms();

	this->reset();
	this->positionCamera();

	glRotatef(-90,1,0,0);
	glFrontFace(GL_CCW);
	
	
	this->renderAllEntities();
	
	glFlush();
	this->flush_callback();
}

void rendererGL::specificInit() {
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
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable( GL_NORMALIZE );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	//glColor3f(0,0,1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	// glEnable( GL_LIGHTING );
	//glEnable(GL_LIGHT0);
	// GLfloat global_ambient[] = { 0, 0, 0 }; 
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	this->setupTexture(w->getSkybox()->getTexture());
	this->setupTexture(w->getTerrain()->getTexture());

	lightbulb=gluNewQuadric();          
	gluQuadricNormals(lightbulb, GLU_SMOOTH);  
	gluQuadricTexture(lightbulb, GL_TRUE);
	ptree & shaders=config::getInstance()->getNode("config.screen.shaders");
	BOOST_FOREACH(const ptree::value_type &shad, shaders) {
		string sn=shad.second.get_value<string>();
		cout << "Adding shader: " << sn << endl;
		addShader(sn);
	}
	//light_shader_v=glCreateShaderObjectARB( GL_VERTEX_SHADER_ARB);
	//char *vf=loadText("data/shaders/toon.vert");
	//char *ff=loadText("data/shaders/toon.frag");
	//addShader("toon");
	
}

void rendererGL::addShader(string name) {
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

char * rendererGL::loadText(string fn) {
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

void rendererGL::renderSkybox(skybox *sky) {
	this->reset();

	glDisable(GL_DEPTH_TEST);
	//	glDisable(GL_LIGHTING);
	this->translate(0,0,-18);
	this->assignTexture(sky->getTexture());
	glBegin(GL_QUADS);
	this->renderPShape(sky->getShape());

	glEnd();
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
}

void rendererGL::assignTexture(texture *t) {
	GLuint tex_id;
	tex_id = this->textures_ids[t];
	glBindTexture(GL_TEXTURE_2D, tex_id);
}

void rendererGL::setupTexture(texture *t) {

	GLuint tex_id;

	glGenTextures(1, &tex_id);
	this->textures_ids[t] = tex_id;
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//for testing
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->getWidth(), t->getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());
}

void rendererGL::translateSpecific(e_loc x, e_loc y, e_loc z) {
	glTranslatef(x,y,z);
}



/*void rendererGL::rotateSpecific(e_loc x,e_loc y,e_loc z) {
this->rotateSpecific(1,0,0,x);
this->rotateSpecific(0,1,0,y);
this->rotateSpecific(0,0,1,z);
}*/

void rendererGL::rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d) {
	glRotatef(d,x,y,z);
}

void rendererGL::resetSpecific() {
	glLoadIdentity();
	glTranslatef(0,0,-frustum_start);
}

void rendererGL::positionCameraSpecific() {
	glRotatef(-90,1,0,0);
}