#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP

#include "rendererAbstract.hpp"

#include <GL/gl.h>

class rendererGL : public renderer {
    virtual void specificInit();
        
    
    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

