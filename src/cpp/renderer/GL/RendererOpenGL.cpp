#include "renderer/GL/RendererOpenGL.hpp"

void RendererOpenGL::init(size_t width, size_t height) {
    glewInit();
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
        cout << "Shaders in place\n";
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 5000);

    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
}

void RendererOpenGL::renderSkybox(Skybox *sky) {
    this->resetMatrix();
    glFrontFace(GL_CCW);

    glDisable(GL_DEPTH_TEST);
    /// glDisable(GL_LIGHTING);

    this->translate(Vector3d(0, 0, -18));
    //glDisable(GL_TEXTURE_2D);
    glColor4f(0, 1, 1, 1);
    this->assignTexture(sky->getTexture());

    Shape *skyshape = sky->getShape();

    
    glBegin(GL_QUADS);
    for (size_t i = 0; i < skyshape->v_count; i++) {
        //glVertex3f(&s->vertices[i], 0, &s->uvs[i]);
        glTexCoord2d(skyshape->uvs[i].u, skyshape->uvs[i].v);
        glVertex3d(skyshape->vertices[i].x, skyshape->vertices[i].y, skyshape->vertices[i].z);
    }
    glEnd();
    glEnable(GL_DEPTH_TEST);
    ///glEnable(GL_LIGHTING);
    glFrontFace(GL_CW);
   // glEnable(GL_TEXTURE_2D);

}

void RendererOpenGL::assignTexture(Texture *t) {
    GLuint tex_id;
    tex_id = this->textures_ids[t];
    glActiveTexture(GL_TEXTURE0);
    //glUniform1i(texloc, 0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
}

void RendererOpenGL::assignMaterial(Material *m) {
    ColorRGBA specular = m->getSpecular(),
            diffuse = m->getDiffuse();

    e_loc shining = m->getShininess(), emit = m->getEmission();

    GLfloat diff[] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
    GLfloat spec[] = {specular.r, specular.g, specular.b, specular.a};
    GLfloat emi[] = {emit, emit, emit, 1};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shining);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emi);
}

void RendererOpenGL::renderShape(Shape *s) {
    size_t ** polys = (size_t **) s->faces;
    size_t uvc = 0;

    for (size_t i = 0; i < s->f_count; i++) {

        if (s->materials && s->materials[i]) {
            this->assignMaterial(s->materials[i]);
        }

        if (s->textures && s->textures[i]) {
            this->assignTexture(s->textures[i]);

        }
        // glColor4f(0,1,0,1);
        glBegin(GL_TRIANGLES);
        for (size_t n = 0; n < s->v_per_poly; n++) {
            glNormal3d(s->faces[i].normals[n].x, s->faces[i].normals[n].y, s->faces[i].normals[n].z);
            glTexCoord2d(s->faces[i].uvs[n].u, s->faces[i].uvs[n].v);
            glVertex3d(s->vertices[s->faces[i].index[n]].x,
                    s->vertices[s->faces[i].index[n]].y,
                    s->vertices[s->faces[i].index[n]].z);

            uvc++;
        }
        glEnd();
    }
}

void RendererOpenGL::render2DShape(Shape2d *shape) {
    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; i++) {
        glTexCoord2d(shape->uvs[i].u, shape->uvs[i].v);
        glNormal3d(shape->normals[i].x, shape->normals[i].y, shape->normals[i].z);
        glVertex3d(shape->vertices[i].x, shape->vertices[i].y, shape->vertices[i].z);

    }
    glEnd();
}

void RendererOpenGL::resetMatrix() {
    glLoadIdentity();
    glTranslatef(0, 0, -2);
}

void RendererOpenGL::beforeFrame() {
    //    glClearColor(1,0,0,1);
    glClear(GL_DEPTH_BUFFER_BIT); //| GL_COLOR_BUFFER_BIT
    glMatrixMode(GL_MODELVIEW);
    //glFrontFace(GL_CW);
}

void RendererOpenGL::afterFrame() {
    glFlush();
}

void RendererOpenGL::translate(Vector3d v) {
    glTranslated(v.x, v.y, v.z);
}

void RendererOpenGL::rotate(Vector3d v, e_loc degrees) {
    glRotatef(degrees, v.x, v.y, v.z);
}

void RendererOpenGL::setupTexture(Texture *t) {
    GLuint tex_id;
    GLint tf;
    textureFormat tformat = t->getFormat();

    switch (tformat) {
        case TF_BGR:
            tf = GL_BGR_EXT;
            break;

        case TF_RGB:
            tf = GL_RGB;
            break;

        case TF_RGBA:
            tf = GL_RGBA;
            break;

        default:
            tf = GL_RGB;
            break;

    }

    glGenTextures(1, &tex_id);
    this->textures_ids[t] = tex_id;
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexStorage2D(GL_TEXTURE_2D, 8, tf, t->getWidth(), t->getHeight());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, t->getWidth(), t->getHeight(), 0, tf, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());

    glGenerateMipmap(GL_TEXTURE_2D);
}

void RendererOpenGL::positionCamera(Camera *camera) {
    Coords c = camera->getCoords();
    this->rotate(Vector3d(1, 0, 0), c.rotation.x);
    this->rotate(Vector3d(0, 1, 0), c.rotation.y);
    this->rotate(Vector3d(0, 0, 1), c.rotation.z);
    this->translate(c.translation);
}


extern "C" {

    void * returnRenderer() {
        return (RendererInterface *) new RendererOpenGL();
    }
}