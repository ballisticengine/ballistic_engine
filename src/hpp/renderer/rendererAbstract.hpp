#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include <iostream>

using namespace std;

#include "misc/singleton.hpp"
#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"
#include "types/skybox.hpp"
#include "world/World.hpp" 
#include "config/Config.hpp"
#include "resources/ResourceManager.hpp"
#include "entities/Camera.hpp"
#include "entities/light.hpp"
#include "types/material.hpp"
#include "types/boundingCube.hpp"
#include "entities/sprite.hpp"
#include "ui/image.hpp"
#include "ui/hud.hpp"

typedef void (*flushf)();

class ModelView;

class RendererAbstract {
    friend class ModelView;
protected:
    HUD *hud;
    EngineState *state;
    VideoData vd;
    float frustum_start, frustum_end, frustum_x, frustum_y;
    Camera *active_Camera;
    flushf flush_callback;
    World *w;
    virtual void renderShape(Shape *s)=0;
    virtual void renderPShape(Shape *s)=0;
    virtual void renderFaceTexShape(Shape *s) = 0;
    virtual void renderSkybox(Skybox *sky) = 0;
    virtual void renderSprite(Sprite *sprite) = 0;
    virtual void lightOff() = 0;
    virtual void lightOn() = 0;
    virtual void renderAllEntities();
    virtual void renderAllRooms();
    virtual void renderAllDecals();
    virtual void renderDecal(Sprite *decal) = 0;
    virtual void setAmbientLight(ColorRGB *c) = 0;
    virtual void assignTexture(Texture *t) = 0;
    virtual void assignMaterial(Material *m) = 0;
    virtual void lightSpecific(Light *l) = 0;
    virtual void drawBoundingBox(BoundingCube *bound) = 0;
    virtual void drawHud() = 0;
    virtual void drawHudImage(UiImage *img) = 0;
    virtual void specificInit() = 0;
    virtual void setupTexture(Texture *t, char *pixels = 0) = 0;
    virtual void setupTextures();
    virtual void positionLights();
    virtual void translate(e_loc x, e_loc y, e_loc z)=0;
    virtual void translate(Coords c);
    virtual void rotate(e_loc x, e_loc y, e_loc z, e_loc d)=0;
    virtual void reset()=0;
    virtual void face(e_loc x, e_loc y, e_loc z);
public:
    RendererAbstract();
     virtual void init();
    virtual void setVideoMode() = 0;
    virtual void setFlush(flushf flush_callback);
    virtual ~RendererAbstract();
    virtual void operator()();
    virtual void render() = 0;
    virtual void setCamera(Camera *c);
    virtual void positionCamera();
};

extern "C" {
    void * returnRenderer();
}
#endif	/* RENDERERABSTRACT_HPP */

