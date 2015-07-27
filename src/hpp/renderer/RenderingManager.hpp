#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"

typedef void (*flush_function)();

class RenderingManager : public Singleton<RenderingManager> {
protected:
     flush_function flush_callback;
     RendererInterface *renderer;
     World *world;
     virtual void renderAllRooms();
     virtual void renderAllEntities();
     virtual void renderAllDecals();
     virtual void face(Vector3d &v);
public:
    RenderingManager();
    ~RenderingManager();
    virtual void setupTextures();
    virtual void init();
    virtual void setRenderer(RendererInterface *renderer);
    virtual RendererInterface * getRenderer();
    virtual void render();
    virtual void setFlush(flush_function flush_callback);
    void positionLights();
};

#endif

