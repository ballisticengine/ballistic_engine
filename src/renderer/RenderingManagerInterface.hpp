#ifndef RENDERINGMANAGERINTERFACE_HPP
#define	RENDERINGMANAGERINTERFACE_HPP

#include "renderer/RendererInterface.hpp"

typedef void (*flush_function)();

class RenderingManagerInterface {
protected:
     RendererInterface *renderer;
     flush_function flush_callback;
public:
    RenderingManagerInterface();
    virtual ~RenderingManagerInterface();
    virtual void setRenderer(RendererInterface *renderer);
    virtual RendererInterface * getRenderer();
    virtual void setFlush(flush_function flush_callback);
    virtual void render()=0;

};

#endif	

