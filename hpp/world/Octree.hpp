#ifndef OCTREE_HPP
#define	OCTREE_HPP

#include <vector>

using namespace std;

#include "entities/RoomEntity.hpp"
#include "types/boundingCube.hpp"
#include "types/shape.hpp"

typedef vector<Face *> face_list;

class OctreeNode {
public:
    OctreeNode *children[8];
    BoundingCube *bounds;
    Shape *shape;
    face_list faces;
    void generate();
};

OctreeNode * generateOctree(rooms_list rooms);


#endif	

