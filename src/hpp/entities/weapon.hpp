#ifndef WEAPON_HPP
#define	WEAPON_HPP

#include <map>
#include <string>

using namespace std;

#include "entities/entity.hpp"
#include "entities/sprite.hpp"
#include "types/mathTypes.hpp"
#include "types/texture.hpp"
#include "types/shape.hpp"
#include "ui/uiMesh.hpp"


class Weapon : public Entity {
public:
    e_loc initial_velocity;
    UiMesh *model;
    Texture *decal; 
    Shape *bullet; 
    string display_name; 
    Weapon *next,*prev;
};

typedef map<string, Weapon *> weapon_map;

#endif	

