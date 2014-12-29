#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cmath>
#include <iostream>

#define PI 3.14159265

typedef double e_loc;

namespace MathTypes {

struct BasicVector {
	e_loc x,y,z;
};

class vector {
protected:
	e_loc ifZero(e_loc value);

public:
	e_loc x,y,z;
	vector(const vector &v);
	vector(const BasicVector &v);
	virtual vector & operator=(const vector &v);
	BasicVector getBasicVector();
	vector();
	virtual vector  unit();
	virtual vector  normalize();
	virtual  vector  diff(const MathTypes::vector & v);
	e_loc length();
	vector  crossProduct(const MathTypes::vector * b); 
	e_loc dotProduct(const MathTypes::vector * b);
	virtual std::ostream & operator<<(std::ostream & ostr);
	virtual void write();
	
	vector  operator+(const vector &b);
	vector  operator-(const vector &b);
	vector  operator/(const e_loc val);
	vector  operator/(const vector &b);
	vector  operator*(const vector &b);
	vector  operator*(const double a);
	//ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx

};

 

} //namespace

e_loc normalizeRotation(e_loc r);

#endif