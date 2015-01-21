#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include <iostream>

using namespace std;

#include "misc/singleton.hpp"
#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"
#include "types/skybox.hpp"
#include "world/world.hpp" 
#include "config/config.hpp"
#include "factories/textureFactory.hpp"
#include "entities/camera.hpp"
#include "entities/light.hpp"
#include "dontcare/terrainMap.hpp"
#include "types/material.hpp"
#include "types/boundingCube.hpp"
#include "entities/sprite.hpp"
#include "ui/image.hpp"
#include "ui/hud.hpp"

typedef void (*flushf)();

class renderer {
protected:
    HUD *hud;
    engineState *state;
    videoData vd;
    float frustum_start, frustum_end, frustum_x, frustum_y;
    camera *active_camera;
    flushf flush_callback;
    world *w;
    virtual void renderShape(shape *s);
    virtual void renderPShape(shape *s);
    virtual void renderFaceTexShape(shape *s)=0;
    virtual void renderVertex(v_type *v, n_type *normal, uv *uvs) = 0;
    virtual void renderSkybox(skybox *sky) = 0;
    virtual void renderSprite(Sprite *sprite) = 0;
    virtual void beginQuads() = 0;
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void beginHinted(shape *s) = 0;
    virtual void lightOff()=0;
    virtual void lightOn()=0;
    virtual void renderAllEntities();
    virtual void renderAllRooms();
    virtual void renderAllDecals();
    virtual void renderDecal(Sprite *decal)=0;
    virtual void setAmbientLight(colorRGB *c) = 0;
    virtual void positionCameraSpecific();

    virtual void assignTexture(texture *t) = 0;
    virtual void assignMaterial(Material *m) = 0;
    virtual void resetSpecific() = 0;
    virtual void lightSpecific(light *l) = 0;
    virtual void drawBoundingBox(BoundingCube *bound) = 0;
    virtual void drawHud() = 0;
    virtual void drawHudImage(UiImage *img) = 0;
    //virtual void renderTerrain();
    virtual void renderTerrainSpecific() = 0;

    coords cursor;
    e_loc gx, gy, gz, gr; //globalne transformacje 
public:
    renderer();
    virtual void setFlush(flushf flush_callback);

    void init();

    virtual void specificInit() {

    };

    virtual void setupTexture(texture *t) {
    }

    virtual void setupTextures();


    virtual void translateSpecific(e_loc x, e_loc y, e_loc z) = 0;
    virtual void rotateSpecific(e_loc x, e_loc y, e_loc z, e_loc d) = 0;



    virtual void positionLights();



    virtual void translate(e_loc x, e_loc y, e_loc z);
    virtual void translate(coords c);
    virtual void rotate(e_loc x, e_loc y, e_loc z, e_loc d);

    virtual void locate(e_loc x, e_loc y, e_loc z);
    virtual void reset();
    virtual void face(e_loc x, e_loc y, e_loc z);
    //todo: locate_delta rotate_delta
    virtual ~renderer();
    virtual void operator()();
    virtual void render() = 0;
    virtual void setCamera(camera *c);
    virtual void positionCamera();
};


#endif	/* RENDERERABSTRACT_HPP */

