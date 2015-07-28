#ifndef RENDEREROPENGL_HPP
#define	RENDEREROPENGL_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer/RendererInterface.hpp"
#include "misc/utils.hpp"



class RendererOpenGL : public RendererInterface {
protected:
    GLint texloc, use_light_glsl, light_set, glsl_bounding;
    map<Texture *, GLuint> textures_ids;
    void assignTexture(Texture *t);
    void assignMaterial(Material *m);
    void addShader(string name);
    GLhandleARB p;
    size_t light_counter;
     map <int, GLint> light_numbers;
public:
    void init(size_t width, size_t height);
    void renderShape(Shape *s);
    void render2DShape(Shape2d *shape);
    void resetMatrix();
    void beforeFrame();
    void afterFrame();
    void translate(Vector3d v);
    void rotate(Vector3d v, e_loc degrees);
    void setupTexture(Texture *t);
    void positionCamera(Camera *camera);
    void renderSkybox(Skybox *sky);
    void addLight(Light *l);
    Vector3d unproject(size_t x, size_t y);
    Vector3d project(Vector3d coords);
};


#endif	
