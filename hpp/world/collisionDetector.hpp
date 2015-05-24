#ifndef COLLISIONDETECTOR_HPP
#define	COLLISIONDETECTOR_HPP

#include "entities/physicalEntity.hpp"
#include "entities/entity.hpp"
#include "entities/RoomEntity.hpp"
#include "types/mathTypes.hpp"


class CollisionDetector {
private:
    Vector3d cTest(BoundingCube *a, BoundingCube *b, Coords offset);
public:
    CollsionInfo objectsCollide(PhysicalEntity *a,PhysicalEntity *b,Coords offset);
    CollsionInfo roomCollide(RoomEntity *r,PhysicalEntity *e,Coords offset);
    
};


#endif	

