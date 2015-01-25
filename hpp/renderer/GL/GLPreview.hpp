#ifndef GLPREVIEW_HPP
#define	GLPREVIEW_HPP

#include <iostream>
#include <string>

using namespace std;

#include "renderer/GL/RendererGL.hpp"
#include "types/shape.hpp"
#include "types/types.hpp"
#include "misc/singleton.hpp"

class GLPreview : public RendererGL,public singleton<GLPreview> {
protected:
    shape* model;
    virtual void specificInit();
   
public:
     coords c;    
    virtual void setModel(shape *model);
    static GLPreview *getInstance();
    virtual void render();
};


#endif	

