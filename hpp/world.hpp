

#ifndef WORLD_HPP
#define	WORLD_HPP

#include "entity.hpp"
#include "singleton.hpp"
#include "skybox.hpp"

class world : public singleton {
protected:
    vector <entity *> entities;
};

#endif	/* WORLD_HPP */

