#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP

#include "rendererAbstract.hpp"

#include <GL/gl.h>
#include <map>

using namespace std;

class rendererGL : public renderer {
    protected:
    map<texture *,GLuint> textures_ids;
    virtual void renderVertex(vertex *v);
    texture *tt;
    
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
    virtual void assignTexture(texture *t);
   
    public:
     virtual void setupTexture(texture *t);    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

