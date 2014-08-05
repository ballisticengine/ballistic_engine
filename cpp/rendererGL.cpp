#include "rendererGL.hpp"
#include "types.hpp"

void rendererGL::renderVertex(vertex *v) {
    glTexCoord2f(v->u, v->v);
    glVertex3f(v->x, v->y, v->z);
}

void rendererGL::render() {

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glTranslatef(0, 0, -frustum_start*5);
    glColor3f(1, 0, 0);

   // this->assignTexture(tt);

    //this->renderSkybox(w->getSkybox());
    glEnable(GL_DEPTH_TEST);
    
    glTranslatef(gx,gy,gz);
    glRotatef(gr,0,1,0);
    
    
    this->assignTexture(qt);
   //  glTranslatef(0,0,-500);
   glBegin(GL_TRIANGLES); 
    this->renderShape(test);
    glEnd();
     //gluSphere(q1,1.3f,32,32);
//    this->assignTexture(qt);
    //glTranslatef(7,2,-3);
    // gluSphere(q1,1.3f,32,32);
    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {

	glViewport(0, 0,config::getInstance()->getVD()->width, config::getInstance()->getVD()->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



    cout << "SI";
    tt = new texture("data/skybox.bmp");
    tt->load();
    this->setupTexture(tt);
    qt=new texture("data/car.bmp");
    qt->load();
    this->setupTexture(qt);
  
    loaderMD2 *loader=loaderMD2::getInstance();
    test=new shape();
    loader->loadMD2("data/test.md2",test);

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