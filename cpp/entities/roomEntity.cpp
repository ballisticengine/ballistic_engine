#include "entities/roomEntity.hpp"

roomEntity::roomEntity() {
    last_bound = 0;
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

//            static int i=0;
//            cout << "hit"<<i<<endl;
//            i++;
            if (bound_current.min.y >= bound->min.y) {
                ctmp.y = COLLISION_BACK;
               // cout << "A";
            }
            else if (bound_current.min.y <= bound->max.y+bound->height) {
                //cout << bound_current.min.y << ", " << bound->min.y << ", " << bound_current.max.y << ", " << bound->max.y << endl;
                ctmp.y = -COLLISION_BACK;
              //  cout << "B";
            }
            if (ox > oz) {
                e_loc dif = am.z - bm.z;
                if (dif > 0) {
                    ctmp.x = COLLISION_BACK;
                } else {
                    ctmp.x = -COLLISION_BACK;
                }
            } else if (oz > ox) {
                e_loc dif = am.x - bm.x;

                if (dif > 0) {
                    ctmp.z = COLLISION_BACK;
                } else {
                    ctmp.z = -COLLISION_BACK;
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





