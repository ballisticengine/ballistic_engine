#ifndef VECTOR3D_HPP
#define	VECTOR3D_HPP

#include <cmath>
#include <iostream>
#include "types/basic_typedefs.hpp"

class Vector3d {
protected:
    scalar_t ifZero(scalar_t value);

public:
    scalar_t x, y, z;
    Vector3d(scalar_t x, scalar_t y, scalar_t z);
    Vector3d(const Vector3d &v);
    Vector3d();
    
    virtual Vector3d & operator=(const Vector3d &v);
    const bool operator==( const Vector3d &v);
    virtual Vector3d unit();
    virtual Vector3d normalize();
    virtual Vector3d diff(const Vector3d & v);
    scalar_t length();
    Vector3d crossProduct(const Vector3d & b);
    scalar_t dotProduct(const Vector3d & b);
    virtual std::ostream & operator<<(std::ostream & ostr);
    virtual void write();
    Vector3d operator^(const Vector3d &b);
    Vector3d operator+(const Vector3d &b);
    Vector3d operator-(const Vector3d &b);
    Vector3d operator-();
    Vector3d operator/(const scalar_t val);
    Vector3d operator/(const Vector3d &b);
    Vector3d operator*(const Vector3d &b);
    Vector3d operator*(const double a);
    scalar_t operator!();
    Vector3d operator|(scalar_t length);
    scalar_t operator%(const Vector3d &b);
};

scalar_t normalizeRotation(scalar_t r);

#endif

