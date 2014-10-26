#include "mathTypes.hpp"

e_loc normalizeRotation(e_loc r) {
	e_loc ra=abs(r);	
	e_loc rmod=fmod(ra,360);
	if(r>=0) {
	 r=rmod;
	} else {
	 r=-rmod;
	}
	return r;
}


namespace MathTypes {

vector::vector() {
 x=y=z=0;
}

vector  & vector::vproduct(const vector & b) {
	//ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx
	vector v;

	v.x=x*b.z-z*b.y;
	v.y=z*b.x-x*b.z;
	v.z=x*b.y-y*b.x;

	return v;
}

vector & vector::unit() {
	vector v;
	v=*this;
	v.x=ifZero(v.x);
	v.y=ifZero(v.y);
	v.z=ifZero(v.z);
	return v;
}

vector::vector(const vector &v) {
 x=v.x;
 y=v.y;
 z=v.z;
}

void vector::operator=(const vector &v) {
	x=v.x;
	y=v.y;
	z=v.z;	
}

e_loc vector::ifZero(e_loc value) {
 if(value>0) {
  return 1;
 } else {
  return 0;
 }
}

}