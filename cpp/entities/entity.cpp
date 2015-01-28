#include "entities/entity.hpp"

coords entity::getCoords() {
    coords c;
    c.translation.x = x;
    c.translation.y = y;
    c.translation.z = z;
    c.rotation.x = rx;
    c.rotation.y = ry;
    c.rotation.z = rz;
    return c;
}

void entity::rotate(e_loc x, e_loc y, e_loc z) {
    this->rx += x;
    this->ry += y;
    this->rz += z;
}

void entity::translate3(e_loc x, e_loc y, e_loc z) {
    this->translate(x, y, z);

}

void entity::translate(e_loc x, e_loc y, e_loc z) {

    this->x += x;
    this->y += y;
    this->z += z;
    for (size_t i = 0; i < boundings.size(); i++) {
        boundings[i]->max.x -= x;
        boundings[i]->max.y -= y;
        boundings[i]->max.z -= z;
        boundings[i]->min.x -= x;
        boundings[i]->min.y -= y;
        boundings[i]->min.z -= z;
        boundings[i]->loc.x = this->x;
        boundings[i]->loc.y = this->y;
        boundings[i]->loc.z = this->z;
    }

}

void entity::locate(e_loc x, e_loc y, e_loc z) {
    this->x = x;
    this->y = y;
    this->z = z;
    for (size_t i = 0; i < boundings.size(); i++) {
        boundings[i]->max.x -= x;
        boundings[i]->max.y -= y;
        boundings[i]->max.z -= z;
        boundings[i]->min.x -= x;
        boundings[i]->min.y -= y;
        boundings[i]->min.z -= z;
        boundings[i]->loc.x = this->x;
        boundings[i]->loc.y = this->y;
        boundings[i]->loc.z = this->z;
    }
}

void entity::syncBounding() {

}

void entity::face(e_loc x, e_loc y, e_loc z) {
    this->rx = x;
    this->ry = y;
    this->rz = z;
}

void entity::translate(coords c) {
    this->translate(c.translation.x, c.translation.y, c.translation.z);
}

entity::entity() {
    
    no_collisions = false;
}

entity::~entity() {
    cout << "Destroying entity" << endl;
    //if (this->bounding_box) {
    //delete this->bounding_box;
    //}
}

/* offset to w�a�ciwie nowa pozycja, a nie przemieszczenie */

MathTypes::vector entity::collides(entity *ent, coords offset)
 {
    
    int i=0,n=0;
    
    BoundingCube *a = boundings[i], *b = ent->boundings[n];

    MathTypes::vector res, offsetx = offset.translation, offsety = offset.translation, offsetz = offset.translation;

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


    MathTypes::vector am, bm;
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

void entity::addBoundingBox(BoundingCube *box) {
    BoundingCube *bounding_box = box;
    bounding_box->max.x -= x;
    bounding_box->max.y -= y;
    bounding_box->max.z -= z;

    bounding_box->min.x -= x;
    bounding_box->min.y -= y;
    bounding_box->min.z -= z;
    boundings.push_back(bounding_box);
}

BoundingCube * entity::getBoundingBox() {
    if(boundings.size()>0) {
    return boundings[0];
    } else {
        return 0;
    }
}

void entity::makeBoundingBox() {
    ///
}

BoundingCube offsetBounding(BoundingCube *bc, coords offset) {
    BoundingCube bcr;
    bcr = *bc;
    bcr.max = bcr.max + offset.translation;
    bcr.min = bcr.min + offset.translation;
    return bcr;
}

bool hitTest(BoundingCube *a, BoundingCube *b, MathTypes::vector offset) {
    MathTypes::vector amax, amin, bmax, bmin;
    amax = a->max + offset;
    amin = a->min + offset;
    bmax = b->max + offset;
    bmin = b->min + offset;

    //offset.write();

    bool collide = (
            amax.x > bmin.x &&
            amin.x < bmax.x &&
            amax.y > bmin.y &&
            amin.y < bmax.y &&
            amax.z > bmin.z &&
            amin.z < bmax.z
            );
    return collide;
}

bool roomHitTest(BoundingCube *a, BoundingCube *b, MathTypes::vector offset) { // tu coś jest źle
    MathTypes::vector amax, amin, bmax, bmin;
    amax = a->max + offset;
    amin = a->min + offset;
    bmax = b->max + offset;
    bmin = b->min + offset;

    //offset.write();

    bool collide = (
            amax.x > bmax.x &&
            amin.x < bmin.x &&
            amax.y > bmax.y &&
            amin.y < bmin.y &&
            amin.z < bmin.z &&
            amax.z > bmax.z
            );
    return collide;
}

