#ifndef GLPREVIEW_HPP
#define	GLPREVIEW_HPP

#include <iostream>
#include <string>

using namespace std;

#include "renderer/GL/RendererGL.hpp"
#include "types/shape.hpp"
#include "types/types.hpp"
#include "misc/singleton.hpp"

class GLPreview : public RendererGL,public Singleton<GLPreview> {
protected:
    Shape* model;
    virtual void specificInit();
    PointLight l;
   
public:
     Coords c;    
    virtual void setModel(Shape *model);
    static GLPreview *getInstance();
    virtual void render();
};


#endif	

