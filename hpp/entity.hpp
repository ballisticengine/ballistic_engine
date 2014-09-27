#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <vector>

using namespace std;

#include "types.hpp"
#include "mathTypes.hpp"

/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

class entity {
protected:
    e_loc x,y,z,rx,ry,rz;
	MathTypes::vector velocity;
public:
	entity();
	coords getCoords();
	void translate(e_loc x,e_loc y,e_loc z);
	void rotate(e_loc x,e_loc y, e_loc z);
	void locate(e_loc x,e_loc y,e_loc z);
	void face(e_loc x,e_loc y,e_loc z);
};

typedef vector<entity *> entity_list;

#endif	/* ENTITY_HPP */

