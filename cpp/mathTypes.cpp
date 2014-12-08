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

std::ostream & vector::operator<<(std::ostream & ostr) {
	ostr << this->x << ", " << this->y << ", " << this->z;
	return ostr;
}

void vector::write() {
	std::cout << this->x << ", " << this->y << ", " << this->z << std::endl;
}

vector  & vector::crossProduct(const MathTypes::vector * b) {
	//ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx
	/*
	 n[0]=va[1]*vb[2] - va[2]*vb[1];
 n[1]=va[2]*vb[0] - va[0]*vb[2];
 n[2]=va[0]*vb[1] - va[1]*vb[0];
	*/
	vector a=*this,v=a;


	v.x=a.y*b->z-a.z*b->y;
	v.y=a.z*b->x-a.x*b->z;
	v.z=a.x*b->y-a.y*b->x;
	
	//v.write();
	return v;
}

vector & vector::unit() {
	/*
	nvx = vx / l
		nvy = vy / l
		nvz = vz / l
	*/
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
 } else if(value<0) {
	return -1;
 }
  return 0;
 
}
vector & vector::diff(const MathTypes::vector & v) {
	vector lv;
	lv.x=x-v.x;
	lv.y=y-v.y;
	lv.z=y-v.z;
	return lv;
}

e_loc vector::length() {
	//vx*vx+vy*vy+vz*vz
	e_loc length=(e_loc)sqrt(x*x+y*y+z*z);
	return length;
}

vector & vector::normalize() {
	vector v=*this;
	v.x/=length();
	v.y/=length();
	v.z/=length();
	return v;
}

e_loc vector::dotProduct(const MathTypes::vector * b) {
	e_loc dp=x*b->x+y*b->y+z*b->z;
	//std::cout <<  << "*" << std::endl;
	return dp;
}

vector & vector::operator+(const vector &b) {
	vector v;
	v.x=this->x+b.x;
	v.y=this->y+b.y;
	v.z=this->z+b.z;
	return v;
}

vector & vector::operator-(const vector &b) {
	vector v;
	v.x=this->x-b.x;
	v.y=this->y-b.y;
	v.z=this->z-b.z;
	return v;
}

vector & vector::operator/(const e_loc val) {
 vector v;
 
 v.x=this->x/val;
 v.y=this->y/val;
 v.z=this->z/val;
 return v;
}

vector & vector::operator/(const vector &b) {
 vector v;
 v.x=this->x/b.x;
 v.y=this->y/b.y;
 v.z=this->z/b.z;
 return v;
}

vector & vector::operator*(const vector &b) {
 vector v;
 v.x=x*b.x;
 v.y=y*b.y;
 v.z=z*b.z;
 return v;
}

}