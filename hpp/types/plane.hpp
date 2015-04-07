#ifndef PLANE_HPP
#define	PLANE_HPP

#include "types/mathTypes.hpp"
#include "types/types.hpp"

class Plane {
public:
    Vector3d N;
    e_loc D;
    Plane(e_loc a=1,e_loc b=0,e_loc c=0,e_loc d=0);
    Plane(Vector3d normal,e_loc d=0);
    Plane(const Plane &plane);
    Plane( Vector3d &a,  Vector3d &b, Vector3d &c);
    const Plane & operator=(const Plane &plane);
    const bool operator==( Plane &plane);
    const bool operator!=( Plane &plane);
    const bool PointOnPlane( Vector3d & point);
    const e_loc DistanceToPlane( Vector3d &point);
    const Vector3d RayIntersection( Vector3d &ray_pos, Vector3d &ray_dir);
};

#endif	/* PLANE_HPP */

