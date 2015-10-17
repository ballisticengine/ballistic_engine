#ifndef RENDERINGACTIONDECORATOR_HPP
#define	RENDERINGACTIONDECORATOR_HPP

#include "renderer/RendererInterface.hpp"

class RenderingActionDecorator {
protected:
    RendererInterface *renderer_interface;
    void *data;
public:
    virtual void setData(void *data);
    virtual void *getData();
    virtual void setRenderer(RendererInterface *renderer_interface);
    virtual void before() {}
    virtual void after() {}
};

#endif	

