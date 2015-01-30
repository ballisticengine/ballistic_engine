#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <vector>

using namespace std;

#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/mathTypes.hpp"
#include "types/boundingCube.hpp"
#define COLLISION_BACK 0.0001

/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

BoundingCube offsetBounding(BoundingCube *bc, coords offset);

bool hitTest(BoundingCube *a, BoundingCube *b, MathTypes::vector offset);
bool roomHitTest(BoundingCube *a,BoundingCube *b,MathTypes::vector offset);

struct collsionInfo {
    MathTypes::vector cvec;
    string nameA,nameB;
    bool collided;
};

class entity {
protected:
    e_loc x, y, z, rx, ry, rz;
    MathTypes::vector velocity;
    virtual MathTypes::vector cTest(BoundingCube *a,BoundingCube *b,coords offset);
    void syncBounding();
public:
    bool no_collisions;
    BoundingCube *bounding_box;
    bounding_list boundings;
    BoundingCube *last_bound;
    entity();
    virtual ~entity();

    virtual coords getCoords();
    string name;
    string type;
    string subtype;
    /*
    Testuje kolizję z innym istnieniem. offset - przemieszczenie względem obecnej pozycji
     */
    virtual collsionInfo collides(entity *ent, coords offset);


    virtual void translate3(e_loc x, e_loc y, e_loc z);
    virtual void translate(e_loc x, e_loc y, e_loc z);
    virtual void translate(coords c);
    virtual void rotate(e_loc x, e_loc y, e_loc z);
    virtual void locate(e_loc x, e_loc y, e_loc z);
    virtual void face(e_loc x, e_loc y, e_loc z);

    virtual void makeBoundingBox();
    
    virtual void addBoundingBox(BoundingCube *box);
    virtual BoundingCube * getBoundingBox();
    string type_hint;
};

typedef vector<entity *> entity_list;

#endif	/* ENTITY_HPP */

