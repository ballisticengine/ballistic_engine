#include "renderer/GL/RendererGL.hpp"
#include "types/types.hpp"

void RendererGL::renderVertex(v_type *v, n_type *normal, UV *uvs) {
    if (normal) {
        glNormal3d(normal->x, normal->y, normal->z);
    }
    if (uvs) {
        glTexCoord2d(uvs->u, uvs->v);
    }
    glVertex3d(v->x, v->y, v->z);
}

void RendererGL::begin() {
    glBegin(GL_TRIANGLES);
}

void RendererGL::beginQuads() {
    glBegin(GL_QUADS);
}

void RendererGL::beginHinted(Shape *s) {
    int count = s->v_per_poly;
    glBegin(count_names[count]);
}

void RendererGL::end() {
    glEnd();
}

void RendererGL::setAmbientLight(ColorRGB *c) {
    GLfloat global_ambient[] = {c->r, c->g, c->b};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void RendererGL::lightSpecific(Light *l) {

    if (light_counter > 7) {
        cout << "Too much lights" << endl;
        return;
    }

    Coords lc = l->getCoords();
    this->reset();

    this->positionCamera();

    this->translate(lc.translation.x, lc.translation.y, lc.translation.z);

    GLfloat position[] = {0, 0, 0, 1.0f};

    if (EngineState::getInstance()->getBool("debug_visual")) {
        glDisable(GL_LIGHTING);
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(1, 0, 0);
        gluSphere(lightbulb, 0.5, 10, 10);
        glEnable(GL_LIGHTING);
        glColor3f(1, 1, 1);
    }

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

RendererGL::RendererGL() {
    light_numbers[0] = GL_LIGHT0;
    light_numbers[1] = GL_LIGHT1;
    light_numbers[2] = GL_LIGHT2;
    light_numbers[3] = GL_LIGHT3;
    light_numbers[4] = GL_LIGHT4;
    light_numbers[5] = GL_LIGHT5;
    light_numbers[6] = GL_LIGHT6;
    light_numbers[7] = GL_LIGHT7;
    count_names[3] = GL_TRIANGLES;
    count_names[4] = GL_QUADS;
}

void RendererGL::renderSprite(Sprite *sprite) {
    this->assignTexture(sprite->tex);

    Coords c = this->w->getObserver()->getCamera()->getCoords();
    float mat[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, mat);


    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++) {
            if (i == j)
                mat[i * 4 + j] = 1.0;
            else
                mat[i * 4 + j] = 0.0;
        }
    glLoadMatrixf(mat);

    //    glBegin(GL_QUADS);
    //    //cout << sprite << endl;
    //    for (size_t i = 0; i < 4; i++) {
    //        glTexCoord2d(sprite->shape->uvs[i].u, sprite->shape->uvs[i].v);
    //        glVertex3d(sprite->shape->vertices[i].x, sprite->shape->vertices[i].y, sprite->shape->vertices[i].z);
    //
    //    }
    //    glEnd();

    renderShape2d(sprite->shape);
}

void RendererGL::renderShape2d(Shape2d *shape) {
    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; i++) {
        glTexCoord2d(shape->uvs[i].u, shape->uvs[i].v);
        glNormal3d(shape->normals[i].x, shape->normals[i].y, shape->normals[i].z);
        glVertex3d(shape->vertices[i].x, shape->vertices[i].y, shape->vertices[i].z);

    }
    glEnd();
}

void RendererGL::lightOff() {
    glUniform1i(use_light_glsl, 0);
}

void RendererGL::lightOn() {
    glUniform1i(use_light_glsl, 1);
}

void RendererGL::drawWeapon(Weapon *weapon) {

    this->reset();

    glTranslated(weapon->model->c.translation.x,
            weapon->model->c.translation.y,
            weapon->model->c.translation.z);
    glRotated(weapon->model->c.rotation.x, 1, 0, 0);
    glRotated(weapon->model->c.rotation.y, 0, 1, 0);
    glRotated(weapon->model->c.rotation.z, 0, 0, 1);
    glScaled(weapon->model->scale,
            weapon->model->scale,
            weapon->model->scale);
    this->renderFaceTexShape(weapon->model->model);
}

void RendererGL::drawHud() {
    image_list images = this->hud->getImages();
    glDisable(GL_DEPTH_TEST);
    this->drawWeapon(this->w->observer.current_weapon);
    this->lightOff();
    for (size_t i = 0; i < images.size(); i++) {
        this->reset();

        glTranslated(images[i]->x, images[i]->y, 0);
        drawHudImage(images[i]);
    }

    this->lightOn();

    glEnable(GL_DEPTH_TEST);

}

void RendererGL::renderDecal(Sprite *decal) {
    this->reset();
    this->positionCamera();
    Coords c = decal->getCoords();
    this->translate(c.translation.x, c.translation.y, c.translation.z);
    this->face(c.rotation.x, c.rotation.y, c.rotation.z);
    this->assignTexture(decal->tex);
    this->renderShape2d(decal->shape);

}

void RendererGL::drawHudImage(UiImage *img) {

    if (img->update) {
        img->update = false;
        this->setupTexture(img->tex);
    }

    this->assignTexture(img->tex);

    this->renderShape2d(img->shape);
}

void RendererGL::render() {

    glClearColor(1, 0, 0, 1);
    glClear(GL_DEPTH_BUFFER_BIT);
    light_counter = 0;
    glMatrixMode(GL_MODELVIEW);
    renderSkybox(w->sky);
    glFrontFace(GL_CW);
   this->reset();
    this->positionCamera();
    this->positionLights();

    this->reset();
    this->positionCamera();
    this->renderAllRooms();
   // this->renderAllDecals();
    this->reset();
    this->positionCamera();
   this->renderAllEntities();
    if (state->getBool("debug_visual")) {
        this->drawBoundingBox(w->observer.getBoundingBox());
    }
   // drawHud();
    glFlush();
    this->flush_callback();

}

void RendererGL::renderFaceTexShape(Shape *s) {

    size_t ** polys = (size_t **) s->faces;
    size_t uvc = 0;
    int dir = *((int *) s->renderer_hint), int_prev_dir;
//    glGetIntegerv(GL_FRONT_FACE, &int_prev_dir);
//    glFrontFace(dir);
    for (size_t i = 0; i < s->f_count; i++) {

        if (s->materials && s->materials[i]) {
            this->assignMaterial(s->materials[i]);
        }

        if (s->textures && s->textures[i]) {
            this->assignTexture(s->textures[i]);

        }

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
//    glFrontFace(int_prev_dir);
}

void RendererGL::setVideoMode() {
    glViewport(0, 0, Config::getInstance()->getVD()->width, Config::getInstance()->getVD()->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 5000);
}

void RendererGL::specificInit() {

    glewInit();
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
        cout << "Shaders in place\n";
    }

    this->setVideoMode();


    //glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);

    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE,GL_S_ALPHA);

    glEnable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glEnable( GL_LIGHTING );
    //glEnable(GL_LIGHT0);


    lightbulb = gluNewQuadric();
    bounding_box_q = gluNewQuadric();
    gluQuadricNormals(lightbulb, GLU_SMOOTH);
    gluQuadricTexture(lightbulb, GL_TRUE);
    gluQuadricNormals(bounding_box_q, GLU_SMOOTH);
    gluQuadricTexture(bounding_box_q, GL_TRUE);
    // hud->addImage("@car.bmp","test",1,1,1,1);


    ptree & shaders = Config::getInstance()->getNode("config.screen.shaders");

    BOOST_FOREACH(const ptree::value_type &shad, shaders) {
        string sn = shad.second.get_value<string>();
        cout << "Adding shader: " << sn << endl;
        addShader(sn);
    }

    //this->setupTexture(this->w->testsprite->tex);
    //this->setUpVbos();


}

void RendererGL::addShader(string name) {
    char *vf = loadText(SHADER_DIR + string(DS) + name + ".vert"), *ff = loadText(SHADER_DIR + string(DS) + name + ".frag");
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


    GLhandleARB p = glCreateProgramObjectARB();
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


    shaders.push_back(p);

}

char * RendererGL::loadText(string fn) {
    char *ft;
    FILE *f = fopen(fn.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    ft = new char[size + 2];

    fread(ft, 1, size, f);
    ft[size] = 0;
    fclose(f);
    return ft;
}

void RendererGL::renderSkybox(Skybox *sky) {
    this->reset();
    glFrontFace(GL_CCW);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    this->lightOff();
    this->translate(0, 0, -18);
    this->assignTexture(sky->getTexture());
    glBegin(GL_QUADS);
    this->renderPShape(sky->getShape());

    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glFrontFace(GL_CW);
    this->lightOn();
}

void RendererGL::assignTexture(Texture *t) {

    GLuint tex_id;
    tex_id = this->textures_ids[t];
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(texloc, 0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
}

void RendererGL::assignMaterial(Material *m) {
    ColorRGBA specular = m->getSpecular(),
            diffuse = m->getDiffuse()
            ;
    e_loc shining = m->getShininess(), emit = m->getEmission()
            ;

    //cout << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << ", " << diffuse.a << endl;
    GLfloat diff[] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
    GLfloat spec[] = {specular.r, specular.g, specular.b, specular.a};
    GLfloat emi[] = {emit, emit, emit, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shining);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emi);


}

void RendererGL::setupTexture(Texture *t, char *pixels) {


    cout << "Setting up " << t->getFilename() << endl;
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
    //glTexStorage2D(GL_TEXTURE_2D, 8, tf, t->getWidth(), t->getHeight());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glTexImage2D(GL_TEXTURE_2D, 0, 4, t->getWidth(), t->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());

    if (pixels) {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, t->getWidth(), t->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) pixels);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, t->getWidth(), t->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());
    }
    glGenerateMipmap(GL_TEXTURE_2D);

}

void RendererGL::translate(e_loc x, e_loc y, e_loc z) {
    glTranslated(x, y, z);
}

void RendererGL::rotate(e_loc x, e_loc y, e_loc z, e_loc d) {
    glRotatef(d, x, y, z);
}

void RendererGL::reset() {
    glLoadIdentity();
    glTranslatef(0, 0, -frustum_start);
}

void RendererGL::drawBoundingBox(BoundingCube *bound) {
    glUniform1i(glsl_bounding, 1);
    this->reset();
    this->positionCamera();
    this->lightOff();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
    glColor3f(0, 1, 0);
    e_loc maxx = bound->max.x, maxy = bound->max.y, maxz = bound->max.z,
            minx = bound->min.x, miny = bound->min.y, minz = bound->min.z;
    ;
    glBegin(GL_QUADS);
    glVertex3d(-minx, -maxy, -maxz);
    glVertex3d(-maxx, -maxy, -maxz);
    glVertex3d(-maxx, -miny, -maxz);
    glVertex3d(-minx, -miny, -maxz);

    glVertex3d(-minx, -miny, -minz);
    glVertex3d(-maxx, -miny, -minz);
    glVertex3d(-maxx, -maxy, -minz);
    glVertex3d(-minx, -maxy, -minz);

    glVertex3d(-minx, -miny, -minz);
    glVertex3d(-minx, -maxy, -minz);
    glVertex3d(-minx, -maxy, -maxz);
    glVertex3d(-minx, -miny, -maxz);


    glVertex3d(-maxx, -miny, -maxz);
    glVertex3d(-maxx, -maxy, -maxz);
    glVertex3d(-maxx, -maxy, -minz);
    glVertex3d(-maxx, -miny, -minz);


    glVertex3d(-minx, -miny, -minz);
    glVertex3d(-minx, -miny, -maxz);
    glVertex3d(-maxx, -miny, -maxz);
    glVertex3d(-maxx, -miny, -minz);


    glVertex3d(-maxx, -maxy, -minz);
    glVertex3d(-maxx, -maxy, -maxz);
    glVertex3d(-minx, -maxy, -maxz);
    glVertex3d(-minx, -maxy, -minz);

    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glColor3f(1, 1, 1);
    this->lightOn();
    glUniform1i(glsl_bounding, 0);
}

void RendererGL::drawBox(e_loc width, e_loc height, e_loc depth) {
    e_loc xx = width / 2, yy = height / 2, zz = depth / 2;
}

void RendererGL::renderPShape(Shape *s) {

    this->begin();
    for (size_t i = 0; i < s->v_count; i++) {
        this->renderVertex(&s->vertices[i], 0, &s->uvs[i]);
    }
    this->end();
}

void RendererGL::renderShape(Shape *s) {

}

extern "C" {

    void * returnRenderer() {
        return (RendererAbstract *) RendererGL::getInstance();
    }
}