#include "renderer/GL/GLPreview.hpp"

void GLPreview::setModel(shape *model) {
    this->model=model;
    c.translation.x=c.translation.y=c.translation.z=c.rotation.x=c.rotation.y=c.rotation.z=0;
    c.translation.z=-100;
}

void GLPreview::specificInit() {
    RendererGL::specificInit();
    lightOff();
    
}
GLPreview *GLPreview::getInstance() {
    return GLPreview::getInstance();
}

void GLPreview::render() {
     glClearColor(1,0,0,1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(c.translation.x,c.translation.y,c.translation.z);
    this->face(c.rotation.x,c.rotation.y,c.rotation.z);
    renderFaceTexShape(model);
    
    glFlush();
    this->flush_callback();
}