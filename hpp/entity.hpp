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
	
	/*
	Testuje kolizję z innym istnieniem. offset - przemieszczenie względem obecnej pozycji
	*/
	virtual bool collides(entity *e,coords offset);
	
	/*
	 Zwraca bryłę otaczającą. Dla świateł, czy abstrakcji zawsze null. 
	 Dla pokojów - je same, dla obiektów wyliczoną bryłę otaczającą. Dla obserwatora pukt w przestrzeni.
	*/
	virtual shape *getBoundingShape();

	void translate(e_loc x,e_loc y,e_loc z);
	void translate(coords c);
	void rotate(e_loc x,e_loc y, e_loc z);
	void locate(e_loc x,e_loc y,e_loc z);
	void face(e_loc x,e_loc y,e_loc z);
};

typedef vector<entity *> entity_list;

#endif	/* ENTITY_HPP */

