#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"
#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"
#include "ui/ui.hpp"
#include "renderer/RenderingManagerEngine.hpp"


class RenderingManager : public RenderingManagerEngine, public Singleton<RenderingManager> {
public:
    RenderingManager();
    ~RenderingManager();
    virtual void render();
    void positionLights();
};

#endif

