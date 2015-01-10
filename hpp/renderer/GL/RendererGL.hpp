#ifndef RendererGL_HPP
#define	RendererGL_HPP
#ifdef _WIN32
#include "windows.h"
#endif
#include "renderer/rendererAbstract.hpp"
#include "loaders/loaderMD2.hpp"
#include "config/config.hpp"
#include "ui/image.hpp"
#include "ui/hud.hpp"
#include "io/sdl2d.hpp"
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

#define BUFFER_OFFSET(i) ((void*)(i))

struct GLHint {
    GLuint vertexid, faceid, normid, uvid;
    vector <GLuint> face_chunks;
    vector<size_t> chunk_sizes;
    vector<texture *> texture_chunks;


};

struct Geom {
    float x, y, z; //,nx,ny,nz,u,v;
};

struct Guv {
    float u, v;
};

class RendererGL : public renderer, public singleton<RendererGL> {
protected:
    GLuint v, f;
    map <int, GLint> light_numbers, count_names;
    int light_counter;
    char * loadText(string fn);
    shader_list shaders;
    
    void addShader(string name);
    map<texture *, GLuint> textures_ids;
    virtual void renderVertex(v_type *v, n_type *normal, uv *uvs);
    texture *tt, *qt;
    shape *test;
    GLUquadricObj *lightbulb, *bounding_box_q;
    GLhandleARB light_shader_v, light_shader_f;
    
    GLint texloc,use_light_glsl,light_set;
    virtual void specificInit();
    virtual void renderSkybox(skybox *sky);
    virtual void renderSprite(Sprite *sprite);
    virtual void assignTexture(texture *t);
    virtual void assignMaterial(Material *m);
    virtual void begin();
    virtual void beginQuads();
    virtual void end();
    virtual void renderShape2d(Shape2d *shape);
    virtual void beginHinted(shape *s);
    virtual void translateSpecific(e_loc x, e_loc y, e_loc z);
    virtual void lightSpecific(light *l);
    virtual void lightOff();
    virtual void lightOn();
    virtual void positionCameraSpecific();
    virtual void rotateSpecific(e_loc x, e_loc y, e_loc z, e_loc d);
    virtual void setAmbientLight(colorRGB *c);
    virtual void drawBoundingBox(BoundingCube *bound);
    virtual void drawHud();
    virtual void drawHudImage(UiImage *img);
    virtual void resetSpecific();
    virtual void drawBox(e_loc width, e_loc height, e_loc depth);

    virtual void renderTerrainSpecific();
    //virtual void renderFaceTexShape(faceTexShape *s);
    void setUpVbos();
    void setUpVbo(shape *s);
     void renderFaceTexShape(shape *s);
    void renderFaceTexShapex(shape *s);
public:
    RendererGL();
    virtual void setupTexture(texture *t);
    virtual void render();
};

#endif	/* RendererGL_HPP */

