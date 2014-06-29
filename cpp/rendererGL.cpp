#include "rendererGL.hpp"
#include "types.hpp"

void rendererGL::renderVertex(vertex *v) {
   glVertex3f(v->x,v->y,v->z);  
}

void rendererGL::render() {
    static texture tex("data/test_texture.bmp");
    shape s;
//    vertex v1(0,0,0),v2(1,1,0),v3(1,0,0),v4(0,1,0);
//    triangle t(&v1,&v4,&v2);
//    triangle t2(&v1,&v2,&v3);
//    tris_list tris;
//    s.addTriangle(&t2);
//    s.addTriangle(&t);
//    
//    tris=s.getTris();
    vertex vs[4]={vertex(0,0,0),vertex(1,1,0),vertex(1,0,0),vertex(0,1,0)};
    s.addVertices(vs,4);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -frustum_start);
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);

    e_loc x,y,z;
    
   // cout << tris.size() << endl;
    this->renderPShape(&s);
    glEnd();
    glFlush();
    this->flush_callback();
}

void rendererGL::specificInit() {
    frustum_start = 1;
    frustum_end = 100;
    glViewport(0, 0, vd.width, vd.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10, 10, -10, 10, frustum_start, frustum_end);
     glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
}

void rendererGL::renderSkybox(skybox *sky) {
    
}