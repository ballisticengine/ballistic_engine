#ifndef RENDERERGL_HPP
#define	RENDERERGL_HPP
#include "windows.h"
#include "rendererAbstract.hpp"
#include "loaderMD2.hpp"
#include "config.hpp"
#include <glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cstdio>

#include <map>

using namespace std;

class rendererGL : public renderer,public singleton<rendererGL> {
    protected:
    char * loadText(string fn);
	void addShader(string name);
	map<texture *,GLuint> textures_ids;
    virtual void renderVertex(vertex *v);
    texture *tt,*qt;
    shape *test;
    GLUquadricObj *lightbulb;   
    GLhandleARB  light_shader_v,light_shader_f;
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
    virtual void assignTexture(texture *t);
	virtual void begin();
	virtual void beginQuads();
	virtual void end();
	virtual void translateSpecific(e_loc x,e_loc y,e_loc z);
	virtual void lightSpecific(light *l);
    //virtual void rotateSpecific(e_loc x,e_loc y,e_loc z);
	virtual void positionCameraSpecific();
	virtual void rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d);
	
	virtual void resetSpecific() ;

	virtual void renderTerrainSpecific();
public:
    rendererGL();
	virtual void setupTexture(texture *t);    
    virtual void render();
};

#endif	/* RENDERERGL_HPP */

