#include "types/skybox.hpp"    

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
	box->vertices=new v_type[4];
	box->uvs=new uv[4];
	box->v_count=4;
	box->vertices[0].x=x;
	box->vertices[0].y=-y;
	box->vertices[0].z=0;
	box->vertices[1].x=-x;
	box->vertices[1].y=-y;
	box->vertices[1].z=0;
	box->vertices[2].x=-x;
	box->vertices[2].y=y;
	box->vertices[2].z=0;
	box->vertices[3].x=x;
	box->vertices[3].y=y;
	box->vertices[3].z=0;
	box->uvs[0].u=1;
	box->uvs[0].v=1;
	box->uvs[1].u=0;
	box->uvs[1].v=1;
	box->uvs[2].u=0;
	box->uvs[2].v=0;
	box->uvs[3].u=1;
	box->uvs[3].v=0;

	/*box->addVertex(new vertex(x,-y,0),new uv(1,1));
    box->addVertex(new vertex(-x,-y,0),new uv(0,1));
	box->addVertex(new vertex(-x,y,0),new uv(0,0));
	box->addVertex(new vertex(x,y,0),new uv(1,0));*/
}

shape * skybox::getShape() {
    return box;
}