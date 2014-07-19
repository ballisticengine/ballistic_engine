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
    glTranslatef(0, 0, -frustum_start);
    glColor3f(1, 0, 0);

    this->assignTexture(tt);

    this->renderSkybox(w->getSkybox());
    glEnable(GL_DEPTH_TEST);
     
    this->assignTexture(qt);
     glTranslatef(0,0,0);
    gluSphere(q1,1.3f,32,32);
    this->assignTexture(tt);
    glTranslatef(0,0,-3);
     gluSphere(q1,1.3f,32,32);
    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {

    glViewport(0, 0, vd.width, vd.height);
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
    qt=new texture("data/checker_small.bmp");
    qt->load();
    this->setupTexture(qt);
    q1 = gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
    gluQuadricNormals(q1, GLU_SMOOTH); // Create Smooth Normals ( NEW )
    gluQuadricTexture(q1, GL_TRUE); // Create Texture Coords ( NEW )
    

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->getWidth(), t->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());
}