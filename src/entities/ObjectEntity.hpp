#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "entities/entity.hpp"
#include "entities/ObjectEntity.hpp"
#include "types/texture.hpp"
#include "types/types.hpp" 
#include "types/material.hpp"
#include "types/shape.hpp"
#include "types/boundingCube.hpp"
#include "entities/texturable.hpp"
#include "time/timer.hpp"

class ObjectEntity : public Entity, public Texturable {
protected:
    void setIfNotZero(scalar_t &a, scalar_t &b);
    Material *mat;
public:
    virtual Shape * getModel();

    Shape *model;
    virtual void setModel(Shape *model);
    Coords velocity, acceleration;
    scalar_t weight;
    ObjectEntity();
    Coords nextCoords(time_int diff);
    void changeVelocity(Coords velocity);
    void setVelocity(Coords velocity);
    bool no_physics;
    Coords getVelocity();
    void printVelocity();
    virtual Material *getMaterial();
    virtual void setMaterial(Material *mat);
    ColorRGBA color; //for color picking



};

#endif