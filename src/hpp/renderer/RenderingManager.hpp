#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"

typedef void (*flush_function)();

class RenderingManager : public Singleton<RenderingManager> {
protected:
     flush_function flush_callback;
     RendererInterface *renderer;
public:
    RenderingManager();
    ~RenderingManager();
    virtual void init();
    virtual void setRenderer(RendererInterface *renderer);
    virtual void render();
    virtual void setFlush(flush_function flush_callback);
};

#endif

