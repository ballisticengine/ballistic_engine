#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cmath>

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
	vector & unit();
	vector & vproduct(const vector & b); 
	//ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx

};

 

} //namespace

e_loc normalizeRotation(e_loc r);

#endif