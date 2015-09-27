#ifndef RENDEREROPENGL_HPP
#define	RENDEREROPENGL_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer/RendererInterface.hpp"
#include "ui/librocket_interfaces/RendererInterfaceSDL2.hpp"
#include "misc/utils.hpp"

class RendererOpenGL : public RendererInterface {
protected:
    GLint texloc, use_light_glsl, light_set, glsl_bounding;
    map<Ballistic::Types::Texture *, GLuint> textures_ids;
    void assignTexture(Ballistic::Types::Texture *t);
    void assignMaterial(Material *m);
    void addShader(string name);
    GLhandleARB p;
    size_t light_counter;
    map <int, GLint> light_numbers;
    Rocket::Core::RenderInterface *ui_renderer;
    Frustum frustum;
    SDLIOInterface *io;
public:
    void init(size_t width, size_t height, SDLIOInterface *io);
    void renderShape(Shape *s);
    void render2DShape(Shape2d *shape);
    void resetMatrix();
    void beforeFrame();
    void afterFrame();
    void translate(Vector3d v);
    void rotate(Vector3d v, e_loc degrees);
    void setupTexture(Ballistic::Types::Texture *t);
    void positionCamera(Camera *camera);
    void renderSkybox(Skybox *sky);
    void addLight(Light *l);
    Vector3d unproject(size_t x, size_t y);
    Vector3d project(Vector3d coords);
    virtual Rocket::Core::RenderInterface * getUiRenderer();
    virtual void setFrustum(Frustum frustum);
    virtual Frustum getFrustum();
    virtual void clear(ColorRGBA color);
};


#endif	
