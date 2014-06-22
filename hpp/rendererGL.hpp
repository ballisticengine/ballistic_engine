#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP

#include "rendererAbstract.hpp"

#include <GL/gl.h>

class rendererGL : public renderer {
    float frustum_start,frustum_end;
    
    virtual void specificInit();
        
    public:
    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

