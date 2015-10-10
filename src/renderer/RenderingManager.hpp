#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"
#include "ui/ui.hpp"
#include "renderer/RenderingManagerInterface.hpp"

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
    virtual void render();
    virtual void positionLights();
    virtual void setupTextures();
 
};

#endif

