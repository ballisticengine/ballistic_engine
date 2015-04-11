#include "types/mathTypes.hpp"

e_loc normalizeRotation(e_loc r) {
    e_loc ra = std::abs(r);
    e_loc rmod = fmod(ra, 360);
    if (r >= 0) {
        r = rmod;
    } else {
        r = -rmod;
    }
    return r;
}

Vector3d::Vector3d() {
    x = y = z = 0;
}

std::ostream & Vector3d::operator<<(std::ostream & ostr) {
    ostr << this->x << ", " << this->y << ", " << this->z;
    return ostr;
}

void Vector3d::write() {
    std::cout << this->x << ", " << this->y << ", " << this->z << std::endl;
}

Vector3d Vector3d::operator^(const Vector3d &b) {
    Vector3d v;
    v.x = y * b.z - z * b.y;
    v.y = z * b.x - x * b.z;
    v.z = x * b.y - y * b.x;
    return v;
}

Vector3d Vector3d::crossProduct(const Vector3d & b) {

    Vector3d a = *this, v = a;

    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;

    return v;
}

Vector3d Vector3d::unit() {
    Vector3d v;
    v = *this;
    v.x = ifZero(v.x);
    v.y = ifZero(v.y);
    v.z = ifZero(v.z);
    return v;
}

Vector3d::Vector3d(const Vector3d &v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3d::Vector3d(e_loc x, e_loc y, e_loc z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3d & Vector3d::operator=(const Vector3d &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

e_loc Vector3d::ifZero(e_loc value) {
    if (value > 0) {
        return 1;
    } else if (value < 0) {
        return -1;
    }
    return 0;

}

Vector3d Vector3d::diff(const Vector3d & v) {
    Vector3d lv;
    lv.x = x - v.x;
    lv.y = y - v.y;
    lv.z = y - v.z;
    return lv;
}

e_loc Vector3d::length() {
    e_loc length = (e_loc) sqrt(x * x + y * y + z * z);
    return length;
}

Vector3d Vector3d::normalize() {
    Vector3d v = *this;
    v.x /= length();
    v.y /= length();
    v.z /= length();
    return v;
}

e_loc Vector3d::dotProduct(const Vector3d & b) {
    e_loc dp = x * b.x + y * b.y + z * b.z;
    return dp;
}

Vector3d Vector3d::operator+(const Vector3d &b) {
    Vector3d v;
    v.x = this->x + b.x;
    v.y = this->y + b.y;
    v.z = this->z + b.z;
    return v;
}

Vector3d Vector3d::operator-(const Vector3d &b) {
    Vector3d v;
    v.x = this->x - b.x;
    v.y = this->y - b.y;
    v.z = this->z - b.z;
    return v;
}

Vector3d Vector3d::operator/(const e_loc val) {
    Vector3d v;

    v.x = this->x / val;
    v.y = this->y / val;
    v.z = this->z / val;
    return v;
}

Vector3d Vector3d::operator/(const Vector3d &b) {
    Vector3d v;
    v.x = this->x / b.x;
    v.y = this->y / b.y;
    v.z = this->z / b.z;
    return v;
}

Vector3d Vector3d::operator*(const Vector3d &b) {
    Vector3d v;
    v.x = x * b.x;
    v.y = y * b.y;
    v.z = z * b.z;
    return v;
}

Vector3d Vector3d::operator*(const double a) {
    Vector3d v;
    v.x = x*a;
    v.y = y*a;
    v.z = z*a;
    return v;
}

e_loc Vector3d::operator!() {
    return sqrt(x * x + y * y + z * z);
}

Vector3d Vector3d::operator|(e_loc length) {
    Vector3d ret;
    ret = *this;
    ret = ret * (length / !ret);
    return ret;
}

e_loc Vector3d::operator%(const Vector3d &b) {
    return dotProduct(b);
}

Vector3d Vector3d::operator-() {
    return Vector3d(-x, -y, -z);
}

const bool Vector3d::operator==(const Vector3d &v) {
    return v.x == x && v.y == y && v.z == z;
}