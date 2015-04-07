#include "types/plane.hpp"

Plane::Plane(e_loc a, e_loc b, e_loc c, e_loc d) {
    N=Vector3d(a,b,c);
    D=d;
}

Plane::Plane(Vector3d normal, e_loc d) {
    N=normal;
    D=d;
}

Plane::Plane(const Plane &plane) {
  N=plane.N;
  D=plane.D;
}

Plane::Plane( Vector3d &vA, Vector3d &vB,  Vector3d &vC) {
    Vector3d normalA,normalB;
    normalA=(vC-vA)|1;
    normalB=(vC-vA)|1;
    N=(normalA^normalB)|1;
    D=-vA % N;
    //normalA=vC-vA;//|1;
}

const Plane & Plane::operator=(const Plane &plane) {
    N=plane.N;
    D=plane.D;
    return *this;
}

const bool Plane::operator==(Plane &plane) {
   return N == plane.N && D == plane.D;
}

const bool Plane::operator!=( Plane &plane) {
    
}

const bool Plane::PointOnPlane( Vector3d & point) {
   return DistanceToPlane(point)==0; 
}

const e_loc Plane::DistanceToPlane( Vector3d &point) {
    return N % point +D;
}

const Vector3d Plane::RayIntersection( Vector3d &ray_pos,  Vector3d &ray_dir) {
    e_loc a=N % ray_dir;
    if (a==0) {
        return ray_pos;
    }
    return ray_pos -  ray_dir * (DistanceToPlane(ray_pos)/a);
}
