#include "skybox.hpp"    

skybox::skybox(string tex_name) {
    //sky=new texture(tex_name);
    if(!sky) {
        cout << "Texture error";
    }
    
}

skybox::skybox(texture *tex) {

}

void skybox::makeShape(float x,float y) {
    /*shape s;
    vertex v1(0,0,0),v2(1,1,0),v3(1,0,0),v4(0,1,0);
    triangle t(&v1,&v4,&v2);
    triangle t2(&v1,&v2,&v3);
    tris_list tris;
    s.addTriangle(&t2);
    s.addTriangle(&t);*/
    box=new shape();
    box->addVertex(x/2,-y/2,0);
    box->addVertex(-x/2,-y/2,0);
    box->addVertex(-x/2,y/2,0);
    box->addVertex(x/2,y/2,0);
}

shape * skybox::getShape() {
    return box;
}