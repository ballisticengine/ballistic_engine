#include "renderer/rendererAbstract.hpp"
#include "types/types.hpp"

RendererAbstract::RendererAbstract() {
    state = EngineState::getInstance();
}

RendererAbstract::~RendererAbstract() {

}

void RendererAbstract::positionLights() {
    lights_list lights = this->w->active_room->lights;
    size_t lights_size = lights.size();

    for (size_t i = 0; i < lights_size; i++) {
        this->lightSpecific(lights[i]);
    }
}

void RendererAbstract::setupTextures() {
    TextureFactory *tf = TextureFactory::getInstance();
    vector<LoadedResource *> ts = tf->getAll();
    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) { 
        this->setupTexture((Texture *) ts[i]->object);
    }
}

void RendererAbstract::renderAllDecals() {
    decal_list decals=this->w->active_room->decals;
    size_t dsize=decals.size();
    for(size_t i=0; i<dsize; i++) {
        renderDecal(decals[i]);
    }
}

void RendererAbstract::init() {
    Config *c = Config::getInstance();
    frustum_start = c->getVD()->frustum_start;
    frustum_end = c->getVD()->frustum_end;
    frustum_x = c->getVD()->frustum_x;
    frustum_y = c->getVD()->frustum_y;
    this->vd = vd;
    this->w = (World *) World::getInstance();
    Skybox *sky = this->w->sky;
    sky->makeShape(frustum_x, frustum_y);
    this->hud = HUD::getInstance();
    this->specificInit();
    cout << "Setting up textueres...\n";
    this->setupTextures();
}

void RendererAbstract::translate(Coords c) {
    this->translate(c.translation.x, c.translation.y, c.translation.z);
}

void RendererAbstract::renderAllEntities() { 
    obj_list ents = w->active_room->models;
    size_t ents_size = ents.size();
    for (size_t i = 0; i < ents_size; i++) {
        Coords c = ents[i]->getCoords();
        this->reset();
        this->positionCamera();
        this->translate(c.translation.x, c.translation.y, c.translation.z);
        this->face(c.rotation.x, c.rotation.y, c.rotation.z); 
        size_t b=0;
        this->renderFaceTexShape(ents[i]->getModel());
        if (state->getBool("debug_visual")) {
            for(b=0; b<ents[i]->boundings.size(); b++) {
                this->drawBoundingBox(ents[i]->boundings[b]);
            }
            b=0;
        }
    }
}

void RendererAbstract::renderAllRooms() {
    rooms_list rooms = w->rooms;
    size_t rooms_size = rooms.size();
    for (size_t i = 0; i < rooms_size; i++) {
        Coords rc=rooms[i]->getCoords();
        this->reset();
        this->positionCamera();
        this->translate(rc.translation.x,rc.translation.y,rc.translation.z);
        this->face(rc.rotation.x,rc.rotation.y,rc.rotation.z);
        this->renderFaceTexShape((Shape *) rooms[i]->getModel());
        if (state->getBool("debug_visual")) {
            size_t boundings_size = rooms[i]->boundings.size();
            for (size_t n = 0; n < boundings_size; n++) {
                this->drawBoundingBox(rooms[i]->boundings[n]);
            }
        }
    }
}

void RendererAbstract::setFlush(flushf flush_callback) {
    this->flush_callback = flush_callback;
}

void RendererAbstract::operator()() {
    
    while (!EngineState::getInstance()->getBool("exit")) {
        this->render();
    }
}

void RendererAbstract::face(e_loc x, e_loc y, e_loc z) { 
    this->rotate(1, 0, 0, x);
    this->rotate(0, 1, 0, y);
    this->rotate(0, 0, 1, z);
}

void RendererAbstract::setCamera(Camera *c) { 
    this->active_Camera = c;
}

void RendererAbstract::positionCamera() {
    Coords c = w->getObserver()->getCamera()->getCoords();
    rotate(1, 0, 0, c.rotation.x);
    rotate(0, 1, 0, c.rotation.y);
    rotate(0, 0, 1, c.rotation.z);
    translate(c.translation.x, c.translation.y, c.translation.z);
}
