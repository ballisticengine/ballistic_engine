#include "entity.hpp"


coords entity::getCoords() {
	coords c;
	c.x=x;
	c.y=y;
	c.z=z;
	c.rx=rx;
	c.ry=ry;
	c.rz=rz;
	return c;
}

void entity::translate(e_loc x,e_loc y,e_loc z) {
 this->x+=x;
 this->y+=y;
 this->z+=z;
}

void entity::rotate(e_loc x,e_loc y, e_loc z) {
 this->rx+=x;
 this->ry+=y;
 this->rz+=z;
}

void entity::locate(e_loc x,e_loc y,e_loc z) {
 this->x=x;
 this->y=y;
 this->z=z;
}

void entity::face(e_loc x,e_loc y,e_loc z) {
 this->rx=x;
 this->ry=y;
 this->rz=z;
}

entity::entity() {
 velocity.x=velocity.y=velocity.z=0;
 

}