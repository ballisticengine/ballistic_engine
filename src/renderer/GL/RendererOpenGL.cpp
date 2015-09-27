#include "renderer/GL/RendererOpenGL.hpp"

Rocket::Core::RenderInterface * RendererOpenGL::getUiRenderer() {
    if (!ui_renderer) {
        ui_renderer = new RocketSDL2Renderer(this, io->getSDLRenderer(), io->getSDLWindow());
    }
    return ui_renderer;
}

void RendererOpenGL::init(size_t width, size_t height, SDLIOInterface *io) {
    this->io = io;
    light_numbers[0] = GL_LIGHT0;
    light_numbers[1] = GL_LIGHT1;
    light_numbers[2] = GL_LIGHT2;
    light_numbers[3] = GL_LIGHT3;
    light_numbers[4] = GL_LIGHT4;
    light_numbers[5] = GL_LIGHT5;
    light_numbers[6] = GL_LIGHT6;
    light_numbers[7] = GL_LIGHT7;
    light_counter = 0;
    glewInit();
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
        cout << "Shaders in place\n";
    }

    glViewport(0, 0, width, height);


    this->setFrustum(Frustum(-2, 2, -2, 2, 2, 5000));

    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    addShader("light");

}

void RendererOpenGL::addLight(Light *l) {
    if (light_counter > 7) {
        cout << "Too much lights" << endl;
        return;
    }


    GLfloat position[] = {0, 0, 0, 1.0f};



    glEnable(light_numbers[light_counter]);
    GLfloat ambientLight[] = {0, 0, 0, 1.0f}; //??
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
    GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    ColorRGBA c = l->getDiffuse();
    GLfloat intensity[] = {c.r, c.g, c.b, c.a};

    GLfloat shin = 0.0001;
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); //??
    glLightfv(light_numbers[light_counter], GL_AMBIENT, intensity);
    glLightfv(light_numbers[light_counter], GL_DIFFUSE, intensity);
    glLightfv(light_numbers[light_counter], GL_SPECULAR, intensity);

    glLightfv(light_numbers[light_counter], GL_POSITION, position);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shin);
    GLfloat ambient[] = {1.0f, 0.0f, 0.0f};
    //glLightf(light_numbers[light_counter], GL_CONSTANT_ATTENUATION, 2);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //this->setAmbientLight(&w->getActiveRoom()->ambient_light);
    light_counter++;
}

void RendererOpenGL::addShader(string name) {
    char *vf = Utils::loadText("data/shaders" + string("/") + name + ".vert"), *ff =
            Utils::loadText("data/shaders" + string("/") + name + ".frag");
    if (!vf || !ff) {
        return;
    }
    const char *vfc = vf, *ffc = ff;
    GLhandleARB vhandle = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB),
            fhandle = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    size_t vfs = strlen(vfc), ffs = strlen(ffc);
    GLint * vs = (GLint*) & vfs, * fs = (GLint*) & ffs;
    glShaderSourceARB(vhandle, 1, &vfc, 0);
    glShaderSourceARB(fhandle, 1, &ffc, 0);
    delete ff;
    delete vf;
    glCompileShaderARB(vhandle);
    glCompileShaderARB(fhandle);
    GLint vcompiled, fcompiled, linked;


    p = glCreateProgramObjectARB();
    glAttachObjectARB(p, vhandle);
    glAttachObjectARB(p, fhandle);
    glLinkProgramARB(p);
    glGetProgramiv(p, GL_LINK_STATUS, &linked);
    glGetObjectParameterivARB(vhandle, GL_COMPILE_STATUS, &vcompiled);
    glGetObjectParameterivARB(vhandle, GL_COMPILE_STATUS, &fcompiled);
    if (!vcompiled || !fcompiled || !linked) {
        cout << "Shader " << name << vcompiled << ", " << fcompiled << "error:\n";
        if (!vcompiled) {
            cout << "Vertex shader error\n";
        }

        if (!fcompiled) {
            cout << "Frament shader error\n";
        }

        if (!linked) {
            cout << "Link error\n";
        }

        GLint blen = 0;
        GLsizei slen = 0;

        glGetShaderiv(p, GL_INFO_LOG_LENGTH, &blen);

        if (blen > 1) {
            GLchar* compiler_log = (GLchar*) malloc(blen);

            glGetInfoLogARB(p, blen, &slen, compiler_log);
            cout << "compiler_log:\n" << compiler_log;
            free(compiler_log);
        }
    }
    glUseProgram(p);
    texloc = glGetUniformLocation(p, "tex");
    use_light_glsl = glGetUniformLocation(p, "use_light");
    glsl_bounding = glGetUniformLocation(p, "bounding");
    light_set = 1;
    glUniform1i(use_light_glsl, light_set);
    glUniform1i(glsl_bounding, 0);
    glUniform1i(glGetUniformLocation(p, "light_count"), 7); //!!


    //shaders.push_back(p);

}

void RendererOpenGL::renderSkybox(Skybox *sky) {
    this->resetMatrix();
    glFrontFace(GL_CCW);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);


    this->translate(Vector3d(0, 0, -18));


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

    glFrontFace(GL_CW);
    glUseProgram(p);


}

void RendererOpenGL::assignTexture(Ballistic::Types::Texture *t) {
    GLuint tex_id;
    tex_id = this->textures_ids[t];
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(texloc, 0);
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
    light_counter = 0;
}

void RendererOpenGL::translate(Vector3d v) {
    glTranslated(v.x, v.y, v.z);
}

void RendererOpenGL::rotate(Vector3d v, e_loc degrees) {
    glRotatef(degrees, v.x, v.y, v.z);
}

void RendererOpenGL::setupTexture(Ballistic::Types::Texture *t) {
    GLuint tex_id;
    GLint tf;
    Ballistic::Types::textureFormat tformat = t->getFormat();

    switch (tformat) {
        case Ballistic::Types::TF_BGR:
            tf = GL_BGR_EXT;
            break;

        case Ballistic::Types::TF_RGB:
            tf = GL_RGB;
            break;

        case Ballistic::Types::TF_RGBA:
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

Vector3d RendererOpenGL::unproject(size_t x, size_t y) {

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (float) x;
    winY = (float) viewport[3] - (float) y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return Vector3d(posX, posY, posZ);
}

Vector3d RendererOpenGL::project(Vector3d coords) {

}

void RendererOpenGL::setFrustum(Frustum frustum) {
    this->frustum = frustum;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
            frustum.left,
            frustum.right,
            frustum.bottom,
            frustum.top,
            frustum.near,
            frustum.far
            );

}

Frustum RendererOpenGL::getFrustum() {
    return this->frustum;
}

void RendererOpenGL::clear(ColorRGBA color) {
   glClearColor(color.r, color.g, color.b, color.a);
   glClear(GL_COLOR_BUFFER_BIT); 
}

extern "C" {

    void * returnRenderer() {
        return (RendererInterface *) new RendererOpenGL();
    }
}