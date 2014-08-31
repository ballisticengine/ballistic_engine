#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "singleton.hpp"
#include "entity.hpp"

/*
Klasa zawiera instacje wszystkich obiektów i przemieszcza je wed³ug danych w nich zawartych
TODO: Wywaliæ, bo to trzeba w world
*/
class entityManager : public singleton<entityManager> {
protected:
	entity_list entities;
public:
}

#endif