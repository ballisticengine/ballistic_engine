#ifndef RENDERINGMIXIN_HPP
#define	RENDERINGMIXIN_HPP

#include <vector>

using namespace std;

#include "renderer/RendererInterface.hpp"
#include "renderer/RenderingActionDecorator.hpp"
#include "world/World.hpp"


class RenderingAction {
protected:
    RendererInterface *renderer;
    vector<void *> params;
    World *world;
    RenderingActionDecorator *decorator;
public:
    RenderingAction();
    virtual void setWorld(World *w);
    virtual void setRenderer(RendererInterface *ri);
    virtual void render()=0;
    virtual void renderWithDecorators();
    virtual void setDecorator(RenderingActionDecorator *decorator, void *data=0);
};


#endif	

