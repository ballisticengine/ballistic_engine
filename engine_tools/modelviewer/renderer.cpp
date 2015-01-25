
#include "renderer.hpp"

void Renderer::basicinit() {
    specificInit();
    
}
void Renderer::render() {
    
    glClearColor(1,0,0,1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);
}