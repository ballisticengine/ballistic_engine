#include "types/plane.hpp"

Plane::Plane(scalar_t a, scalar_t b, scalar_t c, scalar_t d) {
    N = Vector3d(a, b, c);
    D = d;
}

Plane::Plane(Vector3d normal, scalar_t d) {
    N = normal;
    D = d;
}

Plane::Plane(const Plane &plane) {
    N = plane.N;
    D = plane.D;
}

Plane::Plane(Vector3d &vA, Vector3d &vB, Vector3d &vC) {
    Vector3d normalA, normalB;
    normalA = (vC - vA) | 1;
    normalB = (vC - vB) | 1;
    N = (normalB^normalA) | 1;
    D = vA % N;
}

const Plane & Plane::operator=(const Plane &plane) {
    N = plane.N;
    D = plane.D;
    return *this;
}

const bool Plane::operator==(Plane &plane) {
    return N == plane.N && D == plane.D;
}

const bool Plane::operator!=(Plane &plane) {

}

const bool Plane::PointOnPlane(Vector3d & point) {
    double d = 0;
    return DistanceToPlane(point) == d;
}

scalar_t Plane::DistanceToPlane(Vector3d &point) {
    scalar_t dist = N % point + D;
//        if (abs(dist)<1) {
//            dist=floor(dist);
//        }
    return dist;
}

Vector3d Plane::RayIntersection(Vector3d &ray_pos, Vector3d &ray_dir) {
    scalar_t a = N % ray_dir;
    if (a == 0) {
        return ray_pos;
    }
    return ray_pos - (ray_dir * DistanceToPlane(ray_pos) / a);
}

bool pointInPolygon(Vector3d p, Vector3d *points, int n_points) {
    Vector3d segment1, segment2;
    double length1, length2;
    double sum_angles = 0, cos_angle = 0;
    //p.write();
    for (size_t idx = 0; idx < n_points; idx++) {
        segment1 = points[idx] - p;
        
        segment2 = points[(idx + 1) % n_points+1] - p;
        //segment1=segment1.unit();
        //segment2=segment2.unit();
        if (segment1.length() * segment2.length() <= TOLERANCE) {
            sum_angles = TWOPI;
            break;
        }

        cos_angle = (segment1 % segment2) / (segment1.length() * segment2.length());
        sum_angles += cos(cos_angle);

    }
    cout << sum_angles << endl;
    if ((sum_angles <= (TWOPI + TOLERANCE)) && (sum_angles >= (TWOPI - TOLERANCE))) {
        return true;
    } else {
        return false;
    }
}