#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP

#include "rendererAbstract.hpp"

#include <GL/gl.h>

class rendererGL : public renderer {
    protected:
     virtual void renderVertex(vertex *v);
    
    
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
        
    public:
    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

