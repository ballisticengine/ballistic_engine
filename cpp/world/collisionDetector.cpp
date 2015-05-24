#include "world/collisionDetector.hpp"

CollsionInfo CollisionDetector::objectsCollide(PhysicalEntity *ea, PhysicalEntity *eb,Coords offset) {
   int i = 0, n = 0;

    BoundingCube *a = ea->boundings[0], *b = eb->boundings[0], *awin; //nie bwin tylko awin
    e_loc sa = 9999999999999, sb = b->width * b->height;

    Vector3d res;
    bool has_res = false;
    e_loc nsa, nsb;
    for (size_t i = 0; i < ea->boundings.size(); i++) {
        for (size_t n = 0; n < eb->boundings.size(); n++) {
            BoundingCube *a = ea->boundings[i], *b = eb->boundings[n];
            Vector3d cvec = cTest(a, b, offset);
            if (cvec.x || cvec.y || cvec.z) {
                nsa = a->width * a->height;
                if (nsa <= sa) {
                    sa = nsa;
                    //sb = nsb;
                    res = cvec;
                    has_res = true;
                    awin = a;
                }
            }
        }
    }
    CollsionInfo ret;
    if (has_res) {
        ret.collided = true;
        ret.cvec = res;
        ret.nameB = b->name;
        ret.nameA = awin->name;
    } else {
        ret.collided = false;
    }
    return ret; 
 
}

CollsionInfo CollisionDetector::roomCollide(RoomEntity *r, PhysicalEntity *e,Coords offset) {
    CollsionInfo ci;
    return ci;
}

Vector3d CollisionDetector::cTest(BoundingCube *a, BoundingCube *b, Coords offset) {
    Vector3d res, offsetx = offset.translation, offsety = offset.translation, offsetz = offset.translation;

    offsetx.y = offsetx.z = 0;
    offsety.x = offsety.z = 0;
    offsetz.x = offsetz.y = 0;



    res.x = res.y = res.z = 0;

    bool col = hitTest(a, b, offset.translation);


    e_loc

    aright = a->max.x + a->width,
            aleft = a->min.x,
            afront = a->min.z,
            aback = a->max.z + a->depth,

            bleft = b->min.x,
            bright = b->max.x + b->width,
            bfront = b->min.z,
            bback = b->max.z + b->depth,
            halfw = a->width / 2 + b->width / 2,
            halfh = a->height / 2 + b->height / 2,
            halfd = a->depth / 2 + b->depth / 2;


    Vector3d am, bm;
    //cout << "D" << a->width << endl;
    am.x = a->min.x + a->width / 2;
    am.y = a->min.y + a->height / 2;
    am.z = a->min.z + a->depth / 2;

    bm.x = b->min.x + b->width / 2;
    bm.y = b->min.y + b->height / 2;
    bm.z = b->min.z + b->depth / 2;
    e_loc xAxis = abs(bm.x - am.x),
            zAxis = abs(bm.z - am.z),
            yAxis = abs(bm.y - am.y),
            xdif = xAxis - halfw,
            zdif = zAxis - halfd,
            ox = abs(xdif),
            oz = abs(zdif),
            oy = abs(yAxis - halfh)
            ;


    if (!col) {
        return res;
    }


    if (ox > oz) {
        e_loc dif = am.z - bm.z;
        res.x = (bm.z - am.z);
        if (dif) {
            if (dif > 0) {
                res.x = -COLLISION_BACK;
            } else {
                res.x = COLLISION_BACK;
            }
        }
    }



    if (oz > ox) {
        e_loc dif = am.x - bm.x;

        res.z = (bm.x - am.x);
        if (dif > 0) {
            res.z = -COLLISION_BACK;
        } else {
            res.z = COLLISION_BACK;
        }
    }



    if (b->min.y < a->min.y || b->max.y > a->max.y) {

        e_loc dif = am.y - bm.y;
        if (dif > 0) {
            res.y = COLLISION_BACK;
        } else {
            res.y = -COLLISION_BACK;
        }
    }

    return res; 
}