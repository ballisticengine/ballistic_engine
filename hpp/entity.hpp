#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <vector>

using namespace std;

#include "types.hpp"
#include "mathTypes.hpp"
#include "boundingCube.hpp"

/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

class entity {
protected:
    e_loc x,y,z,rx,ry,rz;
	MathTypes::vector velocity;
	BoundingCube *bounding_box;
public:
	entity();
	coords getCoords();
	
	/*
	Testuje kolizję z innym istnieniem. offset - przemieszczenie względem obecnej pozycji
	*/
	virtual bool collides(entity *e);//,coords offset);
	


	void translate(e_loc x,e_loc y,e_loc z);
	void translate(coords c);
	void rotate(e_loc x,e_loc y, e_loc z);
	void locate(e_loc x,e_loc y,e_loc z);
	void face(e_loc x,e_loc y,e_loc z);
	
	virtual void makeBoundingBox();
	virtual void setBoundingBox(BoundingCube *box);
	virtual BoundingCube * getBoundingBox();
};

typedef vector<entity *> entity_list;

#endif	/* ENTITY_HPP */

