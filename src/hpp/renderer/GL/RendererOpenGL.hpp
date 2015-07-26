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
    virtual void init();
    virtual void renderShape(Shape *s);
    virtual void render2DShape(Shape2d *shape);
    virtual void resetMatrix();
    virtual void beforeFrame();
    virtual void afterFrame();
    virtual void translate(Vector3d v);
    virtual void rotate(Vector3d v, e_loc degrees);
    virtual void setupTexture(Texture *t);
    virtual void positionCamera(Camera *c);
};


#endif	
