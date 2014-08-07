#include "rendererGL.hpp"
#include "types.hpp"
#pragma comment(lib, "glu32.lib") 

void rendererGL::renderVertex(vertex *v) {
    glTexCoord2f(v->u, v->v);
    glVertex3f(v->x, v->y, v->z);
}

void rendererGL::begin() {
 glBegin(GL_TRIANGLES); 
}

void rendererGL::end() {
 glEnd();
}

void rendererGL::render() {

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
   
	this->reset();

    
  
	this->renderAllEntities();

    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {

	glViewport(0, 0,config::getInstance()->getVD()->width, config::getInstance()->getVD()->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);
    //gluPerspective(90,1,1,5000);
	glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



   
   

}

void rendererGL::renderSkybox(skybox *sky) {
    glBegin(GL_QUADS);
    this->renderPShape(sky->getShape());

    glEnd();
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

void rendererGL::translateSpecific(float x, float y, float z) {
 glTranslatef(x,y,z);
}



void rendererGL::rotateSpecific(e_loc x,e_loc y,e_loc z) {
	this->rotateSpecific(1,0,0,x);
	this->rotateSpecific(0,1,0,y);
	this->rotateSpecific(0,0,1,z);
}

void rendererGL::rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d) {
 glRotatef(d,x,y,z);
}

void rendererGL::resetSpecific() {
 glLoadIdentity();
 glTranslatef(0,0,-frustum_start);
}

