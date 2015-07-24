#ifndef RENDERERINTERFACE_HPP
#define	RENDERERINTERFACE_HPP

#include "types/types.hpp"
#include "types/shape.hpp"

class RendererInterface {
public:
     virtual void init()=0;
     virtual void renderShape(Shape *s)=0;
};

#endif

