#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cmath>
#include <iostream>

typedef double e_loc;

namespace MathTypes {
class vector {
protected:
	e_loc ifZero(e_loc value);

public:
	e_loc x,y,z;
	vector(const vector &v);
	virtual void operator=(const vector &v);
	
	vector();
	virtual vector & unit();
	virtual vector & normalize();
	virtual  vector & diff(const MathTypes::vector & v);
	e_loc length();
	vector & crossProduct(const MathTypes::vector * b); 
	virtual std::ostream & operator<<(std::ostream & ostr);
	virtual void write();
	//ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx

};

 

} //namespace

e_loc normalizeRotation(e_loc r);

#endif