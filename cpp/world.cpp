#include "world.hpp"

ent_list world::getEntities() {
 
}

skybox * world::getSkybox() {
    return this->sky;
}

 void world::makeTestWorld() {
     this->sky=new skybox("test_texture");
 }