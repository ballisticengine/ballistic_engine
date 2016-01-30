#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <vector>

using namespace std;

#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/Vector3d.hpp"
#include "types/boundingCube.hpp"
#define COLLISION_BACK 0.0001



BoundingCube offsetBounding(BoundingCube *bc, Coords offset);




/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

class Entity {
protected:
    scalar_t x, y, z, rx, ry, rz;
    Vector3d velocity;
    void syncBounding();
public:
    bool no_collisions;
    BoundingCube *bounding_box;
    bounding_list boundings;
    BoundingCube *last_bound;
    Entity();
    virtual ~Entity();

    virtual Coords getCoords();
    string name;
    string type;
    string subtype;
    Entity *parent;
    size_t id;
   
    virtual void translate3(scalar_t x, scalar_t y, scalar_t z);
    virtual void translate(scalar_t x, scalar_t y, scalar_t z);
    virtual void translate(Coords c);
    virtual void rotate(scalar_t x, scalar_t y, scalar_t z);
    virtual void locate(scalar_t x, scalar_t y, scalar_t z);
    virtual void face(scalar_t x, scalar_t y, scalar_t z);

    virtual void makeBoundingBox();
    
    virtual void addBoundingBox(BoundingCube *box);
    virtual BoundingCube * getBoundingBox();
    string type_hint;
    void *physics_data;
};

typedef vector<Entity *> entity_list;

#endif	/* ENTITY_HPP */

