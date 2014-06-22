#include "rendererGL.hpp"

void rendererGL::render() {
    glClearColor(1,1,1,1);  
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-frustum_start);
    glColor3f(1,0,0); 
    glBegin( GL_TRIANGLES );
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);
     
     glEnd();
     glFlush();
     this->flush_callback();
}

void rendererGL::specificInit() {
    frustum_start=1;
    frustum_end=100;
    glViewport( 0, 0, vd.width, vd.height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glFrustum(-10,10,-10,10,frustum_start,frustum_end);
}