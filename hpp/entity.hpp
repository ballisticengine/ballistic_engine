#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <vector>

using namespace std;

#include "types.hpp"
#include "mathTypes.hpp"
#include "boundingCube.hpp"
#define COLLISION_BACK 0.0001;

/*
 Abstrakcyjna klasa opisująca wszystkie obiekty na mapie
 */

BoundingCube offsetBounding(BoundingCube *bc,coords offset);
MathTypes::vector collisionTest(BoundingCube *a,BoundingCube *b,coords offset);
bool hitTest(BoundingCube *a,BoundingCube *b,MathTypes::vector offset);


class entity {
protected:
    e_loc x,y,z,rx,ry,rz;
	MathTypes::vector velocity;
	BoundingCube *bounding_box;
	void syncBounding();
public:
	entity();
	virtual ~entity();

	coords getCoords();
	string name;
	string type;
	/*
	Testuje kolizję z innym istnieniem. offset - przemieszczenie względem obecnej pozycji
	*/
	virtual MathTypes::vector collides(BoundingCube *bound,coords offset);
	


	void translate(e_loc x,e_loc y,e_loc z);
	void translate(coords c);
	void rotate(e_loc x,e_loc y, e_loc z);
	void locate(e_loc x,e_loc y,e_loc z);
	void face(e_loc x,e_loc y,e_loc z);
	
	virtual void makeBoundingBox();
	virtual void setBoundingBox(BoundingCube *box);
	virtual BoundingCube * getBoundingBox();
	string type_hint;
};

typedef vector<entity *> entity_list;

#endif	/* ENTITY_HPP */

