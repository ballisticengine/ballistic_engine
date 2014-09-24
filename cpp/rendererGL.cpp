#include "rendererGL.hpp"
#include "types.hpp"
#pragma comment(lib, "glu32.lib") 

void rendererGL::renderVertex(vertex *v) {
    glTexCoord2d(v->u, v->v);
    glVertex3d(v->x, v->y, v->z);
}

void rendererGL::begin() {
 glBegin(GL_TRIANGLES); 
}

void rendererGL::end() {
 glEnd();
}

void rendererGL::lightSpecific(light *l) {
	
	this->reset();
		this->positionCamera();

  coords c=l->getCoords();
  this->translate(c.x,c.y,c.z);
  //cout << c.x << ", " << c.y << ", " << c.z << endl;
  if(!engineState::getInstance()->light) {
	
    glDisable( GL_LIGHTING );
	  glDisable(GL_TEXTURE_2D);
	glColor3f(0,1,0);
	//gluSphere(lightbulb,2.0f,32,32); 
	glEnable(GL_TEXTURE_2D);
  } else {
   

  }
}

rendererGL::rendererGL() {

}

void rendererGL::render() {

    //glClearColor(0.5, 0.5, 0.5, 1);
    glClear( GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);
   
	renderSkybox(w->getSkybox());
	this->positionLights();
	
	this->reset();
	
	this->positionCamera();

	glRotatef(-90,1,0,0);
	this->renderAllRooms();
	
	this->reset();
	this->positionCamera();
   
	glRotatef(-90,1,0,0);
	
	this->renderAllEntities();

    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {
	//cout << config::getInstance()->getVD()->width;
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
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
    glEnable( GL_LIGHTING );
	this->setupTexture(w->getSkybox()->getTexture());
	
lightbulb=gluNewQuadric();          
gluQuadricNormals(lightbulb, GLU_SMOOTH);  
gluQuadricTexture(lightbulb, GL_TRUE);
}

void rendererGL::renderSkybox(skybox *sky) {
    this->reset();

	glDisable(GL_DEPTH_TEST);
	this->translate(0,0,-18);
	this->assignTexture(sky->getTexture());
	glBegin(GL_QUADS);
    this->renderPShape(sky->getShape());

    glEnd();
	glEnable(GL_DEPTH_TEST);
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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