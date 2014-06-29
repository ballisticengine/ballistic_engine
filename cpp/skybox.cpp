#include "skybox.hpp"    

skybox::skybox(string tex_name) {
    //sky=new texture(tex_name);
    if(!sky) {
        cout << "Texture error";
    }
}

skybox::skybox(texture *tex) {

}

void skybox::makeShape() {
    /*shape s;
    vertex v1(0,0,0),v2(1,1,0),v3(1,0,0),v4(0,1,0);
    triangle t(&v1,&v4,&v2);
    triangle t2(&v1,&v2,&v3);
    tris_list tris;
    s.addTriangle(&t2);
    s.addTriangle(&t);*/
    
}