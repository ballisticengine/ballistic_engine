#include "entities/RoomEntity.hpp"

RoomEntity::RoomEntity() {
    last_bound = 0;
    preload_store = PreloadStore::getInstance();
}

RoomEntity::~RoomEntity() {
    deleteVector(this->boundings);
    deleteVector(this->entities); //to usunie modele, physical_entities i entities z powodo hierarchii (patrz add*Entity)
}

void RoomEntity::addEntity(Entity *e) {
    this->entities.push_back(e);
}

void RoomEntity::addPhysicalEntity(PhysicalEntity *e) {
    this->phys_entities.push_back(e);
    this->addEntity(e);
}

void RoomEntity::addObjectEntity(ObjectEntity *e) {
    this->models.push_back(e);

    this->addPhysicalEntity(e);
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

void RoomEntity::placeDecalTexture(Texture *tex, Coords c) {
    Sprite *decal = new Sprite(tex);
    placeDecal(decal, c);
}

void RoomEntity::placePreloadDecal(string preload, Coords c) {
    Texture *tex = preload_store->tex_preloads[preload];
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

CollsionInfo RoomEntity::collides(Entity *ent, Coords offset) {

    CollsionInfo ci;
    return ci;
}

void RoomEntity::calcBoundings() {
    for (size_t i = 0; i < model->f_count; i++) {
        BoundingCube *bc = new BoundingCube();
        bc->max.x = bc->min.x = bc->max.y = bc->min.y = bc->max.z = bc->min.z = 0;
        /*
         for (unsigned int i=0; i<s->v_count; i++) {
               if (s->vertices[i].x > max.x) {
                       max.x=s->vertices[i].x;
               }

               if(s->vertices[i].x < min.x) {
                min.x=s->vertices[i].x;
               }

               if (s->vertices[i].y > max.y) {
                       max.y=s->vertices[i].y;
               }

               if(s->vertices[i].y < min.y) {
                min.y=s->vertices[i].y;
               }

               if (s->vertices[i].z > max.z) {
                       max.z=s->vertices[i].z;
               }

               if(s->vertices[i].z < min.z) {
                min.z=s->vertices[i].z;
               }
       }*/
        for (size_t n = 0; n < 3; n++) {
            if (model->vertices[model->faces[i].index[n]].x > bc->max.x) {
                bc->max.x = model->vertices[model->faces[i].index[n]].x+this->getCoords().translation.x;
            }
            if (model->vertices[model->faces[i].index[n]].x < bc->min.x) {
                bc->min.x = model->vertices[model->faces[i].index[n]].x+this->getCoords().translation.x;
            }

            if (model->vertices[model->faces[i].index[n]].y > bc->max.y) {
                bc->max.y = model->vertices[model->faces[i].index[n]].y+this->getCoords().translation.y;
            }

            if (model->vertices[model->faces[i].index[n]].y < bc->min.y) {
                bc->min.y = model->vertices[model->faces[i].index[n]].y+this->getCoords().translation.y;
            }

            if (model->vertices[model->faces[i].index[n]].z > bc->max.z) {
                bc->max.z = model->vertices[model->faces[i].index[n]].z+this->getCoords().translation.z;
            }

            if (model->vertices[model->faces[i].index[n]].z < bc->min.z) {
                bc->min.z = model->vertices[model->faces[i].index[n]].z+this->getCoords().translation.z;
            }
        }
      
     
        boundings.push_back(bc);
    }
}


