#include "world/Octree.hpp"

void OctreeNode::generate() {
    
}

OctreeNode * generateOctree(rooms_list rooms) { 
    OctreeNode *node;
    node->shape=rooms[0]->model;
    node->generate();
    return node;
}