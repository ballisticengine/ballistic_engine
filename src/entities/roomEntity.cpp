#include "entities/RoomEntity.hpp"

RoomEntity::RoomEntity() {
    last_bound = 0;
    preload_store = PreloadStore::getInstance();
}

RoomEntity::~RoomEntity() {
    deleteVector3d(this->boundings);
    deleteVector3d(this->entities); //to usunie modele, physical_entities i entities z powodo hierarchii (patrz add*Entity)
}

void RoomEntity::addEntity(Entity *e) {
    this->entities.push_back(e);
    entity_counter++;
}
void RoomEntity::addObjectEntity(ObjectEntity *e) {
    this->models.push_back(e);
}

void RoomEntity::addLightEntity(Light *e) {
    this->lights.push_back(e);
    this->addEntity(e);
}

void RoomEntity::placeDecal(Sprite *decal, Coords c) {

    decal->locate(c.translation.x, c.translation.y, c.translation.z);
    decal->face(c.rotation.x, c.rotation.y, c.rotation.z);
    decals.push_back(decal);
}

void RoomEntity::placeDecalTexture(Ballistic::Types::Texture *tex, Coords c) {
    Sprite *decal = new Sprite(tex);
    placeDecal(decal, c);
}

void RoomEntity::placePreloadDecal(string preload, Coords c) {
    Ballistic::Types::Texture *tex = preload_store->tex_preloads[preload];
    Sprite *decal = new Sprite(tex);
    placeDecal(decal, c);
}

ObjectEntity * RoomEntity::spawnObject(string preload_name, Coords c, string object_name) {
    RoomEntity * room = this;
    return spawnShape(preload_store->shape_preloads[preload_name], c, object_name);
}

ObjectEntity * RoomEntity::spawnShape(Shape *s, Coords c, string object_name) {
    RoomEntity * room = this;
    ObjectEntity *oe = new ObjectEntity();
    oe->setModel(s);
    oe->locate(-c.translation.x, -c.translation.y, -c.translation.z);
    oe->face(c.rotation.x, c.rotation.y, c.rotation.z);
    oe->addBoundingBox(new BoundingCube(oe->getModel()));
    oe->name = object_name;
    oe->type = "object";
    room->addObjectEntity(oe);
    return oe;
}

void RoomEntity::removeObjectEntity(string name) {
    size_t i;
    for (i = 0; i < models.size(); i++) {
        if (models[i]->name == name) {
            break;
        }
    }
    models.erase(models.begin() + i);
}

void RoomEntity::calcBoundings() {
    
}


