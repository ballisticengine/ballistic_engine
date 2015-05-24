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

CollsionInfo RoomEntity::collides(PhysicalEntity *ent, Coords offset) {
    //ray_pos jest już w ent
    CollsionInfo ci;
    Vector3d a,b,c;
    
    bool pos=false;
    e_loc sum=0;
    for(size_t i=0; i<model->f_count; i++) {
      
        a=model->vertices[model->faces[i].index[0]];
        b=model->vertices[model->faces[i].index[1]];
        c=model->vertices[model->faces[i].index[2]];
        a=a+getCoords().translation;
        b=b+getCoords().translation;
        c=c+getCoords().translation;
       // a.y*=-1;b.y*=-1;c.y*=-1;
        Plane p(a,b,c);
        Vector3d v=ent->getCoords().translation;
        Vector3d r=ent->velocity.translation.normalize();
        
        e_loc dist=p.DistanceToPlane(v);
        //cout << dist << endl;
      
        sum+=dist;

        Vector3d ri=p.RayIntersection(v,r);
        //r.write();
        Vector3d tri[3];
        tri[0]=a;
        tri[1]=b;
        tri[2]=c;
       
        bool pip=pointInPolygon(ri,tri,3);
        //cout << pip << endl;
       
       //cout << p.DistanceToPlane(v) << endl;

        
        
        
    }
  
    return ci;
}

void RoomEntity::calcBoundings() {
    
}


