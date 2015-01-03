#include "renderer/GL/RendererGL.hpp"
#include "types/types.hpp"
#pragma comment(lib, "glu32.lib") 

void RendererGL::renderVertex(v_type *v, n_type *normal, uv *uvs) {
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

void RendererGL::beginHinted(shape *s) {
    int count = s->v_per_poly;
    glBegin(count_names[count]);
}

void RendererGL::end() {
    glEnd();
}

void RendererGL::setAmbientLight(colorRGB *c) {
    GLfloat global_ambient[] = {c->r, c->g, c->b};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void RendererGL::renderTerrainSpecific() {
    /*TerrainMap *tm=w->getTerrain();
    shape *s=tm->getQuads();
    vert_list verts;

    this->assignTexture(w->getTerrain()->getTexture());
    glBegin(GL_QUADS);
    for(int i=0; i<tm->getQuadCount(); i++) {

            verts=s[i].getVertices();

            for(int v=0; v<verts.size(); v++) {
                    glVertex3f(verts[v]->x,verts[v]->y,verts[v]->z);
            }

    }
    glEnd();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
     */
}

void RendererGL::lightSpecific(light *l) {

    if (light_counter > 7) {
        cout << "Too much lights" << endl;
        return;
    }



    coords lc = l->getCoords();
    this->reset();

    this->positionCamera();

    //glRotatef(-90,1,0,0);


    this->translate(lc.translation.x, lc.translation.y, lc.translation.z);

    //glRotatef(-90,1,0,0);
    GLfloat position[] = {0, 0, 0, 1.0f};

    //glDisable(GL_LIGHTING);
    if (engineState::getInstance()->debug_visual) {
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
    colorRGBA c = l->getDiffuse();
    GLfloat intensity[] = {c.r, c.g, c.b, c.a};

    GLfloat shin = 30;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); //??
    glLightfv(light_numbers[light_counter], GL_AMBIENT, ambientLight);
    glLightfv(light_numbers[light_counter], GL_DIFFUSE, intensity);
    glLightfv(light_numbers[light_counter], GL_SPECULAR, intensity);

    glLightfv(light_numbers[light_counter], GL_POSITION, position);

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

    //glPushMatrix();
    coords c = this->w->getObserver()->getCamera()->getCoords();
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
    //glPopMatrix();
}

void RendererGL::renderShape2d(Shape2d *shape) {
    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; i++) {
        glTexCoord2d(shape->uvs[i].u, shape->uvs[i].v);
        glVertex3d(shape->vertices[i].x, shape->vertices[i].y, shape->vertices[i].z);

    }
    glEnd();
}

void RendererGL::drawHud() {
    image_list images = this->hud->getImages();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    for (size_t i = 0; i < images.size(); i++) {
        this->reset();

        glTranslated(images[i]->x, images[i]->y, 0);
        drawHudImage(images[i]);
    }
    glEnable(GL_LIGHTING);
    this->reset();
    glTranslated(hud->mesh->c.translation.x,hud->mesh->c.translation.y,hud->mesh->c.translation.z);
    glRotated(hud->mesh->c.rotation.x,1,0,0);
    glRotated(hud->mesh->c.rotation.y,0,1,0);
    glRotated(hud->mesh->c.rotation.z,0,0,1);
    glScaled(hud->mesh->scale,hud->mesh->scale,hud->mesh->scale);
    //this->renderFaceTexShape(hud->mesh->model);
    glEnable(GL_DEPTH_TEST);
    
}

void RendererGL::drawHudImage(UiImage *img) {
    HUD *h=HUD::getInstance();
    UiImage *i=h->getImage("test");
    Draw2d *d=Draw2d::getInstance();
    d->setSurface(i->tex->getSurface());
    d->text("test123");
    img->tex->setSurface(d->surf);
    this->setupTexture(img->tex);
    this->assignTexture(img->tex);
    
    this->renderShape2d(img->shape);
}

void RendererGL::render() {

    //glClearColor(1,1,1,1);
    glClear(GL_DEPTH_BUFFER_BIT);
    light_counter = 0;
    glMatrixMode(GL_MODELVIEW);


    renderSkybox(w->sky);
    //glFrontFace(GL_CW);

    this->positionLights();
    this->reset();

    this->positionCamera();

    this->reset();

    this->positionCamera();



    this->renderAllRooms();

    this->reset();
    this->positionCamera();

    this->renderAllEntities();
    if (state->debug_visual) {
        this->drawBoundingBox(w->observer.getBoundingBox());
    }
    drawHud();
    glFlush();
    this->flush_callback();

}

void RendererGL::renderFaceTexShapex(faceTexShape *s) {





    GLHint *hint = (struct GLHint *) (s->renderer_hint);

    //cout << "CS: " << hint->face_chunks.size() << ", " << hint->chunk_sizes[0] << endl;

    glBindBuffer(GL_ARRAY_BUFFER, hint->vertexid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBufferARB(GL_ARRAY_BUFFER, hint->normid);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, 0);

    cout << hint->texture_chunks.size() << endl;
    for (size_t i = 0; i < hint->face_chunks.size(); i++) {
        glBindBuffer(GL_ARRAY_BUFFER, hint->uvid);
        glClientActiveTexture(GL_TEXTURE0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        this->assignTexture(hint->texture_chunks[i]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hint->face_chunks[i]);
        glDrawElements(count_names[s->v_per_poly], hint->chunk_sizes[i] * s->v_per_poly, GL_UNSIGNED_INT, 0);
    }
    //glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, hint->faceid);
    //glDrawElements(count_names[s->v_per_poly], s->f_count*s->v_per_poly, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RendererGL::setUpVbo(shape *s) {
    Geom *g = new Geom[s->v_count], *ns = new Geom[s->v_count];
    Guv *guvs = new Guv[s->f_count * s->v_per_poly];
    GLuint **chunk_faces;
    GLuint *faces = new GLuint[s->f_count * s->v_per_poly];
    vector<size_t> chunk_sizes;
    int n = 0;

    int chunked_i = 0, chunked_count = 0, c_indice = 0;


    GLHint *hint = new GLHint();

    texture * current_texture;
    int ci = -1;
    for (size_t i = 0; i < s->f_count; i++) {
        if (s->textures[i]) {
            current_texture = s->textures[i];
            chunk_sizes.push_back(0);
            ci++;

        }
        chunk_sizes[ci]++;

    }


    chunk_faces = new GLuint*[chunk_sizes.size()];
    for (size_t i = 0; i < chunk_sizes.size(); i++) {
        chunk_faces[i] = new GLuint[chunk_sizes[i] * s->v_per_poly];
        //hint->face_chunks=new GLuint[chunk_sizes[i]];
        //hint->texture_chunks=new texture*[chunk_sizes[i]];
    }

    ci = -1;
    for (size_t i = 0; i < s->f_count; i++) {
        if (s->textures[i]) {

            ci++;
            hint->texture_chunks.push_back(s->textures[i]);
            n = 0;
        }
        for (size_t v = 0; v < s->v_per_poly; v++) {
            chunk_faces[ci][n] = s->faces[i][v];
            n++;
        }
    }

    for (size_t i = 0; i < s->v_count; i++) {
        g[i].x = s->vertices[i].x;
        g[i].y = s->vertices[i].y;
        g[i].z = s->vertices[i].z;
        ns[i].x = s->normals[i].x;
        ns[i].y = s->normals[i].y;
        ns[i].z = s->normals[i].z;

    }

    size_t uc = 0;
    for (size_t i = 0; i < s->f_count; i++) {
        for (size_t n = 0; n < s->v_per_poly; n++) {
            guvs[s->faces[i][n]].u = s->uvs[s->faces[i][n]].u;
            guvs[s->faces[i][n]].v = s->uvs[s->faces[i][n]].v;
            uc++;
        }
    }

    GLuint vid;
    glGenBuffers(1, &(hint->vertexid));
    glGenBuffers(1, &(hint->normid));
    glGenBuffers(1, &(hint->uvid));
    //glGenBuffers(1,&(hint->faceid));

    glBindBuffer(GL_ARRAY_BUFFER, hint->vertexid);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBufferData(GL_ARRAY_BUFFER, s->v_count * sizeof (Geom), g, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, hint->normid);
    glEnableClientState(GL_NORMAL_ARRAY);
    glBufferData(GL_ARRAY_BUFFER, s->v_count * sizeof (Geom), ns, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, hint->uvid);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBufferData(GL_ARRAY_BUFFER, s->v_count * sizeof (Guv), guvs, GL_STATIC_DRAW);

    unsigned int chunkid;
    for (size_t i = 0; i < chunk_sizes.size(); i++) {

        glGenBuffers(1, &chunkid);
        hint->face_chunks.push_back(chunkid);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hint->face_chunks[i]);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk_sizes[i] * sizeof (GLuint) * s->v_per_poly, chunk_faces[i], GL_STATIC_DRAW);
    }

    hint->chunk_sizes = chunk_sizes;
    s->renderer_hint = hint;
}

void RendererGL::setUpVbos() {
    obj_list models = this->w->getActiveRoom()->models;
    for (size_t i = 0; i < models.size(); i++) {
        setUpVbo(models[i]->getModel());

    }
    setUpVbo(this->w->getActiveRoom()->getModel());

}

void RendererGL::specificInit() {
    glewInit();
    /*if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
     cout << "Shaders in place\n";
    }*/

    glViewport(0, 0, config::getInstance()->getVD()->width, config::getInstance()->getVD()->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-frustum_x, frustum_x, -frustum_y, frustum_y, frustum_start, frustum_end);
    gluPerspective(90, 1, 1, 5000);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

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

    UiMesh *mesh=new UiMesh("@gun.xml",0,0,-10);
    mesh->scale=0.5;
    mesh->c.translation.x=100;
    mesh->c.translation.y=-50;
   mesh->c.translation.z=-150; 
   mesh->c.rotation.y=90;
   mesh->c.rotation.x=-45;
    hud->mesh=mesh;
    ptree & shaders = config::getInstance()->getNode("config.screen.shaders");
    //	BOOST_FOREACH(const ptree::value_type &shad, shaders) {
    //		string sn=shad.second.get_value<string>();
    //		cout << "Adding shader: " << sn << endl;
    //		addShader(sn);
    //	}	

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
    GLhandleARB p = glCreateProgramObjectARB();
    glAttachObjectARB(p, vhandle);
    glAttachObjectARB(p, fhandle);
    glLinkProgramARB(p);


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

void RendererGL::renderSkybox(skybox *sky) {
    this->reset();
    glFrontFace(GL_CCW);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    this->translate(0, 0, -18);
    this->assignTexture(sky->getTexture());
    glBegin(GL_QUADS);
    this->renderPShape(sky->getShape());

    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glFrontFace(GL_CW);
}

void RendererGL::assignTexture(texture *t) {
    GLuint tex_id;
    tex_id = this->textures_ids[t];
    glBindTexture(GL_TEXTURE_2D, tex_id);
}

void RendererGL::assignMaterial(Material *m) {
    colorRGBA specular = m->getSpecular(),
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

void RendererGL::setupTexture(texture *t) {

    GLuint tex_id;

    glGenTextures(1, &tex_id);
    this->textures_ids[t] = tex_id;
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexStorage2D(GL_TEXTURE_2D, 8, GL_BGR_EXT, t->getWidth(), t->getHeight());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //for testing
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->getWidth(), t->getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLvoid *) t->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void RendererGL::translateSpecific(e_loc x, e_loc y, e_loc z) {
    glTranslated(x, y, z);
}

void RendererGL::rotateSpecific(e_loc x, e_loc y, e_loc z, e_loc d) {
    glRotatef(d, x, y, z);
}

void RendererGL::resetSpecific() {
    glLoadIdentity();
    glTranslatef(0, 0, -frustum_start);
}

void RendererGL::positionCameraSpecific() {
    //glRotatef(-90,1,0,0);
}

void RendererGL::drawBoundingBox(BoundingCube *bound) {
    //drawBox(bound->getWidth(),bound->getHeight(),bound->getDepth());
    this->reset();
    this->positionCamera();
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
}

void RendererGL::drawBox(e_loc width, e_loc height, e_loc depth) {
    e_loc xx = width / 2, yy = height / 2, zz = depth / 2;




}