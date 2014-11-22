#include "skybox.hpp"    

skybox::skybox(string tex_name) {
    sky=new texture(tex_name);
    if(! sky->load()) {
        cout << "Texture error";
        cout.flush();
    }
    cout << tex_name << endl;
   
    
}

skybox::skybox(texture *tex) {

}

texture *skybox::getTexture() {
    return this->sky;
}

void skybox::makeShape(float x,float y) {

    box=new shape();
    box->addVertex(new vertex(x,-y,0),new uv(1,1));
    box->addVertex(new vertex(-x,-y,0),new uv(0,1));
	box->addVertex(new vertex(-x,y,0),new uv(0,0));
	box->addVertex(new vertex(x,y,0),new uv(1,0));
}

shape * skybox::getShape() {
    return box;
}