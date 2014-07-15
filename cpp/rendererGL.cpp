#include "rendererGL.hpp"
#include "types.hpp"

void rendererGL::renderVertex(vertex *v) {
   glVertex3f(v->x,v->y,v->z);  
}

void rendererGL::render() {
   
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -frustum_start);
    glColor3f(1, 0, 0);
    
   this->renderSkybox(w->getSkybox());
//    glBegin(GL_TRIANGLES);
//
//  
//    glEnd();
    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {
   
    glViewport(0, 0, vd.width, vd.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);
     glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
}

void rendererGL::renderSkybox(skybox *sky) {
   glBegin(GL_QUADS);
   this->renderPShape(sky->getShape());
     
    glEnd(); 
}