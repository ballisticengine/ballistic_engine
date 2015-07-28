#ifndef RENDERERINTERFACE_HPP
#define	RENDERERINTERFACE_HPP

#include "entities/Camera.hpp"
#include "types/types.hpp"
#include "types/mathTypes.hpp"
#include "types/shape.hpp"
#include "types/shape2d.hpp"
#include "types/skybox.hpp"
#include "entities/light.hpp"

class RendererInterface {
public:
    //TODO: lighting refactor 

    virtual void init(size_t width, size_t height) = 0;
    virtual void renderShape(Shape *s) = 0;
    virtual void render2DShape(Shape2d *shape) = 0;
    virtual void renderSkybox(Skybox *sky)=0;
    virtual void resetMatrix() = 0;
    virtual void beforeFrame() = 0;
    virtual void afterFrame() = 0;
    virtual void translate(Vector3d v) = 0;
    virtual void rotate(Vector3d v, e_loc degrees) = 0;
    virtual void setupTexture(Texture *t) = 0;
    virtual void positionCamera(Camera *c) =0;
    virtual void addLight(Light *l)=0;
    virtual Vector3d unproject(size_t x, size_t y)=0;
    virtual Vector3d project(Vector3d coords)=0;

};

#endif

