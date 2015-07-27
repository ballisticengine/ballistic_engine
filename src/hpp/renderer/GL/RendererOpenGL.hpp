#ifndef RENDEREROPENGL_HPP
#define	RENDEREROPENGL_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer/RendererInterface.hpp"

class RendererOpenGL : public RendererInterface {
protected:
    GLint texloc, use_light_glsl, light_set, glsl_bounding;
    map<Texture *, GLuint> textures_ids;
    void assignTexture(Texture *t);
    void assignMaterial(Material *m);
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
};


#endif	
