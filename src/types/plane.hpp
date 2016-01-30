#ifndef PLANE_HPP
#define	PLANE_HPP

#include "types/Vector3d.hpp"
#include "types/types.hpp"

#define TOLERANCE 0.0000001
#define TWOPI 6.28318530718 
#define RADTOGED 57.2957795

class Plane {
public:
    Vector3d N;
    scalar_t D;
    Plane(scalar_t a=1,scalar_t b=0,scalar_t c=0,scalar_t d=0);
    Plane(Vector3d normal,scalar_t d=0);
    Plane(const Plane &plane);
    Plane( Vector3d &a,  Vector3d &b, Vector3d &c);
    const Plane & operator=(const Plane &plane);
    const bool operator==( Plane &plane);
    const bool operator!=( Plane &plane);
    const bool PointOnPlane( Vector3d & point);
    scalar_t DistanceToPlane( Vector3d &point);
    Vector3d RayIntersection( Vector3d &ray_pos, Vector3d &ray_dir);
};

bool pointInPolygon(Vector3d p,Vector3d *points,int n_points);

#endif	/* PLANE_HPP */

