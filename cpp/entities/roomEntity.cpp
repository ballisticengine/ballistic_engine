#include "entities/roomEntity.hpp"

roomEntity::roomEntity() {
    last_bound = 0;
    preload_store=PreloadStore::getInstance();
}

roomEntity::~roomEntity() {
    deleteVector(this->boundings);
    deleteVector(this->entities); //to usunie modele, physical_entities i entities z powodo hierarchii (patrz add*Entity)
}

void roomEntity::addEntity(entity *e) {
    this->entities.push_back(e);
}

void roomEntity::addPhysicalEntity(PhysicalEntity *e) {
    this->phys_entities.push_back(e);
    this->addEntity(e);
}

void roomEntity::addObjectEntity(ObjectEntity *e) {
    this->models.push_back(e);

    this->addPhysicalEntity(e);
}

void roomEntity::addLightEntity(light *e) {
    this->lights.push_back(e);
    this->addEntity(e);
}

void roomEntity::placeDecal(Sprite *decal,coords c) {
    decal->locate(c.translation.x,c.translation.y,c.translation.z);
    decal->face(c.rotation.x,c.rotation.y,c.rotation.z);
    decals.push_back(decal);
}

void roomEntity::placePreloadDecal(string preload,coords c) {
    texture *tex=preload_store->tex_preloads[preload];
    Sprite *decal=new Sprite(tex);
    placeDecal(decal,c);
}

ObjectEntity * roomEntity::spawnObject(string preload_name,coords c,string object_name) {
//    moving_lock = true;
    roomEntity * room = this;
    ObjectEntity *oe = new ObjectEntity();
    oe->setModel(preload_store->shape_preloads[preload_name]);
    
    oe->locate(-c.translation.x,-c.translation.y,-c.translation.z);
    oe->face(-90, 0, 0);
    oe->setBoundingBox(new BoundingCube(oe->getModel()));
    oe->name=object_name;
    oe->type="object";
    room->addObjectEntity(oe);
    return oe;
}


MathTypes::vector roomEntity::collides(entity *ent,coords offset) {
    BoundingCube *bound=ent->bounding_box;
    e_loc in_count = 0, out_count = 0;
    in_count = out_count = 0;
    BoundingCube bound_off = *bound, bound_current, *in_bounding;
    MathTypes::vector tmp;


    MathTypes::vector cvec, ctmp, cres, none, am, bm, dm;

    e_loc smallest_dist = 999999;

    /*
     UWAGA:
     * jeśli punkt startowy będzie poza wszystkimi bryłami kolizji, to poniższe spowoduje GPF - wywali program
     */
    
    for (size_t i = 0; i < boundings.size(); i++) {
        bound_current = offsetBounding(bound, offset);
        bool col = roomHitTest(boundings[i], &bound_current, offset.translation);
        
       
        if (col) {
            //cout << ent->name << ent->last_bound << endl;
            in_bounding = boundings[i];
            if (!ent->last_bound) {
                ent->last_bound = in_bounding;
            }
            in_count++;
        } else if ( boundings[i] == ent->last_bound) {
            ctmp.x = ctmp.y = ctmp.z = 0;
         

            bound_current = offsetBounding(ent->last_bound, offset);
        
            am.x = bound_current.min.x + bound_current.width / 2;
            am.y = bound_current.min.y + bound_current.height / 2;
            am.z = bound_current.min.z + bound_current.depth / 2;
            bm.x = bound->min.x + bound->width / 2;
            bm.y = bound->min.y + bound->height / 2;
            bm.z = bound->min.z + bound->depth / 2;
            e_loc halfw = bound_current.width / 2 + bound->width / 2,
                    halfh = bound_current.height / 2 + bound->height / 2,
                    halfd = bound_current.depth / 2 + bound->depth / 2;
            e_loc xAxis = abs(bm.x - am.x),
                    zAxis = abs(bm.z - am.z),
                    yAxis = abs(bm.y - am.y),
                    xdif = xAxis - halfw,
                    zdif = zAxis - halfd,
                    ox = abs(xdif),
                    oz = abs(zdif),
                    oy = abs(yAxis - halfh)
                    ;
            bool zside=(bound_current.min.z<bound->min.z || bound_current.max.z>bound->max.z) ,
                    xside=(bound_current.min.x>bound->min.x || bound_current.max.x<bound->max.x),
                    yside=(bound_current.min.y>bound->min.y || bound_current.max.y<bound->max.y);
            //cout << ox << ", " << oy << ", " << oz << endl;
            if (yside ) { // && !(xside && zside)
                if(bound_current.min.y>bound->min.y) {
                    ctmp.y=COLLISION_BACK;
                } else if(bound_current.max.y<bound->max.y) {
                    ctmp.y=-COLLISION_BACK;
                }

            }

            if (xside ) {
                if (bound_current.min.x>bound->min.x) {
                    ctmp.x=COLLISION_BACK;
                } else if(bound_current.max.x<bound->max.x) {
                    ctmp.x=-COLLISION_BACK;
                }
            } else if (zside && !yside) {
                if(bound_current.min.z<bound->min.z) {
                    ctmp.z=-COLLISION_BACK;
                } else if(bound_current.max.z>bound->max.z) {
                    ctmp.z=COLLISION_BACK;
                }
            }

            dm = am - bm;
            e_loc dist = dm.length();
            //if (abs(dist)<smallest_dist) {

            cvec = ctmp;
            //}
            out_count++;
        }
    }

   // cout << in_count << ", " << out_count << endl;
    if (in_count == 0) {
        //cvec.write();
        return cvec;

    } else {

        ent->last_bound = in_bounding;
    }

    return none;
}





