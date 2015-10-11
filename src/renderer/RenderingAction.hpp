#ifndef RENDERINGMIXIN_HPP
#define	RENDERINGMIXIN_HPP

#include <vector>

using namespace std;

#include "renderer/RendererInterface.hpp"
#include "world/World.hpp"


class RenderingAction {
protected:
    RendererInterface *renderer;
    vector<void *> params;
    World *world;
public:
    RenderingAction();
    virtual void setWorld(World *w);
    virtual void setRenderer(RendererInterface *ri);
    virtual void render()=0;
};


#endif	

