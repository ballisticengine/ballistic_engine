#ifndef RENDERINGMIXIN_HPP
#define	RENDERINGMIXIN_HPP

#include <vector>

using namespace std;

#include "renderer/RendererInterface.hpp"


class RenderingAction {
protected:
    RendererInterface *renderer;
public:
    RenderingAction(RendererInterface *renderer_interface, vector<void *> params=vector<void *>());
    virtual void render()=0;
};


#endif	

