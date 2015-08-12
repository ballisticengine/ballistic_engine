#ifndef RENDERERINTERFACE_HPP
#define	RENDERERINTERFACE_HPP

#include "entities/Camera.hpp"
#include "types/types.hpp"
#include "types/Vector3d.hpp"
#include "types/shape.hpp"
#include "types/shape2d.hpp"
#include "types/skybox.hpp"
#include "entities/light.hpp"

class RendererInterface {
public:
    //TODO: lighting refactor 

    virtual void init(size_t width, size_t height) { };
    virtual void renderShape(Shape *s) { };
    virtual void render2DShape(Shape2d *shape) { };
    virtual void renderSkybox(Skybox *sky){ };
    virtual void resetMatrix() { };
    virtual void beforeFrame() { };
    virtual void afterFrame() { };
    virtual void translate(Vector3d v) { };
    virtual void rotate(Vector3d v, e_loc degrees) { };
    virtual void setupTexture(Texture *t) { };
    virtual void positionCamera(Camera *c) { };
    virtual void addLight(Light *l){ };
    virtual Vector3d unproject(size_t x, size_t y){ };
    virtual Vector3d project(Vector3d coords){ };

};

#endif

