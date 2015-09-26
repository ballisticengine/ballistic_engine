#ifndef VECTOR3D_HPP
#define	VECTOR3D_HPP

#include <cmath>
#include <iostream>
#include "types/basic_typedefs.hpp"

class Vector3d {
protected:
    e_loc ifZero(e_loc value);

public:
    e_loc x, y, z;
    Vector3d(e_loc x, e_loc y, e_loc z);
    Vector3d(const Vector3d &v);
    Vector3d();
    
    virtual Vector3d & operator=(const Vector3d &v);
    const bool operator==( const Vector3d &v);
    virtual Vector3d unit();
    virtual Vector3d normalize();
    virtual Vector3d diff(const Vector3d & v);
    e_loc length();
    Vector3d crossProduct(const Vector3d & b);
    e_loc dotProduct(const Vector3d & b);
    virtual std::ostream & operator<<(std::ostream & ostr);
    virtual void write();
    Vector3d operator^(const Vector3d &b);
    Vector3d operator+(const Vector3d &b);
    Vector3d operator-(const Vector3d &b);
    Vector3d operator-();
    Vector3d operator/(const e_loc val);
    Vector3d operator/(const Vector3d &b);
    Vector3d operator*(const Vector3d &b);
    Vector3d operator*(const double a);
    e_loc operator!();
    Vector3d operator|(e_loc length);
    e_loc operator%(const Vector3d &b);
};

e_loc normalizeRotation(e_loc r);

#endif

