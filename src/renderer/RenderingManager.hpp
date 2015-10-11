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
public:
    RenderingManager();
    ~RenderingManager();
    virtual void render();
    virtual void setupTextures();
 
};

#endif

