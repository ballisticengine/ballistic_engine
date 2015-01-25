#ifndef RENDERER_HPP
#define	RENDERER_HPP

#include "renderer/GL/RendererGL.hpp"

class Renderer : public RendererGL {
    public:
        virtual void render();
        virtual void basicinit();
};

#endif	

