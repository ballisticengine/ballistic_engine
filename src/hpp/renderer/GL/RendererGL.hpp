#ifndef RendererGL_HPP
#define	RendererGL_HPP

#ifdef _WIN32
#include "windows.h"
#endif
#include "renderer/rendererAbstract.hpp"
#include "loaders/LoaderMD2.hpp"
#include "config/Config.hpp"
#include "ui/image.hpp"
#include "ui/hud.hpp"
#include "io/ttf.hpp"
extern "C" { 
#ifdef _WIN32
#include <glew.h>
#else 
#include <GL/glew.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
}
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
    vector<Texture *> texture_chunks;
};

struct Geom {
    float x, y, z; //,nx,ny,nz,u,v;
};

struct Guv {
    float u, v;
};

extern "C" { 
class RendererGL : public RendererAbstract, public Singleton<RendererGL> {
protected:
    GLuint v, f;
    map <int, GLint> light_numbers, count_names;
    int light_counter;
    char * loadText(string fn);
    shader_list shaders;
    void addShader(string name);
    map<Texture *, GLuint> textures_ids;
    virtual void renderVertex(v_type *v, n_type *normal, UV *uvs);
    Texture *tt, *qt;
    Shape *test;
    GLUquadricObj *lightbulb, *bounding_box_q;
    GLhandleARB light_shader_v, light_shader_f;
    GLint texloc,use_light_glsl,light_set,glsl_bounding;
    virtual void specificInit();
    virtual void renderSkybox(Skybox *sky);
    virtual void renderSprite(Sprite *sprite);
    virtual void assignTexture(Texture *t);
    virtual void assignMaterial(Material *m);
    virtual void begin();
    virtual void beginQuads();
    virtual void end();
    virtual void renderShape2d(Shape2d *shape);
    virtual void beginHinted(Shape *s);
    virtual void translate(e_loc x, e_loc y, e_loc z);
    virtual void lightSpecific(Light *l);
    virtual void lightOff();
    virtual void lightOn();
    virtual void rotate(e_loc x, e_loc y, e_loc z, e_loc d);
    virtual void setAmbientLight(ColorRGB *c);
    virtual void drawBoundingBox(BoundingCube *bound);
    virtual void drawHud();
    virtual void drawHudImage(UiImage *img);
    virtual void reset();
    virtual void drawWeapon(Weapon *weapon);
    virtual void drawBox(e_loc width, e_loc height, e_loc depth);
    virtual void renderDecal(Sprite *decal);
    void renderPShape(Shape *s);
    void renderShape(Shape *s);
    void setUpVbos();
    void setUpVbo(Shape *s);
    void renderFaceTexShape(Shape *s);
    void renderFaceTexShapex(Shape *s);
public:
    RendererGL();
     virtual void setVideoMode();
    virtual void setupTexture(Texture *t,char *pixels=0);
    virtual void render();
};

}
#endif	/* RendererGL_HPP */

