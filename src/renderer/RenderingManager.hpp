#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"
#include "ui/ui.hpp"
#include "RenderingManagerInterface.hpp"




class RenderingManager : public RenderingManagerInterface, public Singleton<RenderingManager> {
protected:
     World *world;
     virtual void renderAllRooms();
     virtual void renderAllEntities();
     virtual void renderAllDecals();
     virtual void face(Vector3d &v);
public:
    RenderingManager();
    ~RenderingManager();
    virtual void setupTextures();
//    virtual void setRenderer(RendererInterface *renderer);
//    virtual RendererInterface * getRenderer();
    virtual void render();
//    virtual void setFlush(flush_function flush_callback);
    void positionLights();
};

#endif

