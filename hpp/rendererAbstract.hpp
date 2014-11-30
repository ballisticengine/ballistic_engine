#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include <iostream>

using namespace std;

#include "singleton.hpp"
#include "types.hpp"
#include "facetexShape.hpp"
#include "texture.hpp"
#include "skybox.hpp"
#include "world.hpp" //TODO: przenieœæ logikê do world
#include "config.hpp"
#include "textureFactory.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "terrainMap.hpp"
#include "material.hpp"
#include "boundingCube.hpp"

typedef void (*flushf)();

class renderer  {
protected:
    videoData vd;
    float frustum_start, frustum_end, frustum_x, frustum_y; 
    camera *active_camera;
	flushf flush_callback;
    world *w;
    virtual void renderShape(shape *s);
    virtual void renderPShape(shape *s);
	virtual void renderFaceTexShape(faceTexShape *s);
    virtual void renderVertex(vertex *v,uv *uvs) = 0;
    virtual void renderSkybox(skybox *sky) = 0;
	virtual void beginQuads()=0;
	virtual void begin()=0;
	virtual void end()=0;
	virtual void beginHinted(shape *s)=0;

	virtual void renderAllEntities();
	virtual void renderAllRooms();
	
	virtual void positionCameraSpecific();

    virtual void assignTexture(texture *t)=0;
	virtual void assignMaterial(Material *m)=0;
	virtual void resetSpecific()=0;
	virtual void lightSpecific(light *l)=0;
	virtual void drawBoundingBox(BoundingCube *bound)=0;

	//virtual void renderTerrain();
	virtual void renderTerrainSpecific()=0;
    
		coords cursor ;
		e_loc gx,gy,gz,gr; //globalne transformacje 
public:
    renderer();
    virtual void setFlush(flushf flush_callback);

    void init();

    virtual void specificInit() {

    };

    virtual void setupTexture(texture *t) {
    }

	virtual void setupTextures();

    
	virtual void translateSpecific(e_loc x,e_loc y,e_loc z)=0;
	virtual void rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d)=0;
	
	

	virtual void positionLights();
	


	virtual void translate(e_loc x, e_loc y, e_loc z);
	virtual void translate(coords c);
	virtual void rotate(e_loc x,e_loc y,e_loc z,e_loc d);
	
	virtual void locate(e_loc x,e_loc y,e_loc z);
	virtual void reset();
	virtual void face(e_loc x,e_loc y,e_loc z);
	//todo: locate_delta rotate_delta
    virtual ~renderer();
    virtual void operator()();
    virtual void render() = 0;
	virtual void setCamera(camera *c);
	virtual void positionCamera();
};


#endif	/* RENDERERABSTRACT_HPP */

