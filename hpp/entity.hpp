#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include "types.hpp"


/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

class entity {
protected:
    e_loc x,y,z,rx,ry,rz;
public:
	coords getCoords();
	void translate(e_loc x,e_loc y,e_loc z);
	void rotate(e_loc x,e_loc y, e_loc z);

};


#endif	/* ENTITY_HPP */

