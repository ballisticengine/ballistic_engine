#ifndef WEAPON_HPP
#define	WEAPON_HPP

#include <map>
#include <string>

using namespace std;

#include "entities/entity.hpp"
#include "types/mathTypes.hpp"
#include "types/texture.hpp"
#include "types/shape.hpp"
#include "ui/uiMesh.hpp"


class Weapon : public entity {
public:
    e_loc initial_velocity;
    UiMesh *model;
    texture *decal;
    shape *bullet;
    string display_name; 
};

typedef map<string, Weapon *> weapon_map;

#endif	

