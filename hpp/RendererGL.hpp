#ifndef RendererGL_HPP
#define	RendererGL_HPP
#ifdef _WIN32
#include "windows.h"
#endif
#include "rendererAbstract.hpp"
#include "loaderMD2.hpp"
#include "config.hpp"
#ifdef _WIN32
#include <glew.h>
#else 
#include <GL/glew.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <map>
#include <vector>

using namespace std;
using boost::property_tree::ptree;

typedef vector<GLhandleARB> shader_list;



class RendererGL : public renderer,public singleton<RendererGL> {
    protected:
    map <int,GLint> light_numbers,count_names;
	int light_counter;
	char * loadText(string fn);
	shader_list shaders;
	void addShader(string name);
	map<texture *,GLuint> textures_ids;
    virtual void renderVertex(v_type *v,n_type *normal,uv *uvs) ;
    texture *tt,*qt;
    shape *test;
    GLUquadricObj *lightbulb,*bounding_box_q;   
    GLhandleARB  light_shader_v,light_shader_f;
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
    virtual void assignTexture(texture *t);
	virtual void assignMaterial(Material *m);
	virtual void begin();
	virtual void beginQuads();
	virtual void end();
	virtual void beginHinted(shape *s);
	virtual void translateSpecific(e_loc x,e_loc y,e_loc z);
	virtual void lightSpecific(light *l);
    //virtual void rotateSpecific(e_loc x,e_loc y,e_loc z);
	virtual void positionCameraSpecific();
	virtual void rotateSpecific(e_loc x,e_loc y,e_loc z,e_loc d);
	virtual void setAmbientLight(colorRGB *c);
	virtual void drawBoundingBox(BoundingCube *bound);

	virtual void resetSpecific() ;

	virtual void drawBox(e_loc width,e_loc height,e_loc depth);

	virtual void renderTerrainSpecific();
	//virtual void renderFaceTexShape(faceTexShape *s);
	void setUpVbos();
public:
    RendererGL();
	virtual void setupTexture(texture *t);    
    virtual void render();
};

#endif	/* RendererGL_HPP */

