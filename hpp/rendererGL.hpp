#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP

#include "rendererAbstract.hpp"
#include "loaderMD2.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <map>

using namespace std;

class rendererGL : public renderer {
    protected:
    map<texture *,GLuint> textures_ids;
    virtual void renderVertex(vertex *v);
    texture *tt,*qt;
    shape *test;
    GLUquadricObj *q1,*q2;   
    
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
    virtual void assignTexture(texture *t);
   
    public:
     virtual void setupTexture(texture *t);    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

