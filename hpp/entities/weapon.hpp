#ifndef WEAPON_HPP
#define	WEAPON_HPP

#include <map>
#include <string>

using namespace std;

#include "entities/ObjectEntity.hpp"
#include "types/mathTypes.hpp"
#include "types/texture.hpp"
#include "types/shape.hpp"



class Weapon : public ObjectEntity {
public:
    e_loc initial_velocity;
    texture *decal;
    shape *bullet;
    string display_name;
    
};

typedef map<string, Weapon *> weapon_map;

#endif	

