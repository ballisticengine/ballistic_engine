#include "rendererGL.hpp"

void rendererGL::render() {
    
}

void rendererGL::specificInit() {
    glViewport( 0, 0, vd.width, vd.height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glFrustum(-10,10,-10,10,1,100);
}