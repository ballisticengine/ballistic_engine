

#ifndef WORLD_HPP
#define	WORLD_HPP

#include "entity.hpp"
#include "singleton.hpp"
#include "skybox.hpp"

typedef vector <entity *> ent_list;

class world : public singleton {
protected:
    ent_list entities;
    skybox *sky;
    public:
        ent_list getEntities();
        skybox * getSkybox();
        void makeTestWorld();
};

#endif	/* WORLD_HPP */

