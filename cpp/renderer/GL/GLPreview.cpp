#include "renderer/GL/GLPreview.hpp"

void GLPreview::setModel(shape *model) {
    this->model=model;
    c.translation.x=c.translation.y=c.translation.z=c.rotation.x=c.rotation.y=c.rotation.z=0;
    c.translation.z=-10;
    c.rotation.x=-90;
   
    l.locate(0,0,-10);
    colorRGBA cl;
    cl.r=1;
    cl.g=1;
    cl.b=1;
    cl.a=1;
    l.setAllColors(cl);
}

void GLPreview::specificInit() {
    RendererGL::specificInit();
    lightOff();
    //glFrontFace(GL_CW);
    
}
GLPreview *GLPreview::getInstance() {
    return GLPreview::getInstance();
}

void GLPreview::render() {
     glClearColor(0.5,0.5,0.5,1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    this->lightSpecific(&l);
    glLoadIdentity();
    
    glTranslatef(c.translation.x,c.translation.y,c.translation.z);
    this->face(c.rotation.x,c.rotation.y,c.rotation.z);
    renderFaceTexShape(model);
    
    glFlush();
    this->flush_callback();
}