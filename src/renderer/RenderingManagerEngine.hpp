#ifndef RENDERINGMANAGERENGINE_HPP
#define	RENDERINGMANAGERENGINE_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"
#include "ui/ui.hpp"
#include "renderer/RenderingManagerInterface.hpp"

class RenderingManagerEngine : public RenderingManagerInterface {
protected:
     World *world;
     virtual void renderAllRooms();
     virtual void renderAllEntities();
     virtual void renderAllDecals();
     virtual void face(Vector3d &v);
public:
    virtual void setupTextures();
    virtual void render();
    virtual void positionLights();
};

#endif	

