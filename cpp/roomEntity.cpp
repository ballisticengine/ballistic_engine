#include "roomEntity.hpp"


roomEntity::roomEntity() {

}
	
shape *roomEntity::getBoundingShape() {
	return this->model;
}

/*

int SphereToPlaneCollision(const Plane& plane, const Sphere& sphere)
{
    float dot = dot_product(plane.normal,sphere.m_Center) - plane.offset;
 
    if(dot > sphere.m_Radius)
        return 1; // The sphere is in front of the plane
    else if(dot < -sphere.m_Radius)
        return 2; // The sphere is behind the plane
 
    return 3; // The sphere collides/straddles with the plane
}
int AabbToPlaneCollision(const Plane& plane, const AABB& aabb)
{
    // Get the Extense vector
    Vector3 E = (aabb.max - aabb.min)/2.0f;
    
    // Get the center of the Box
    Vector3 center = aabb.min + E;
 
    Vector3 N = plane.normal;
 
    // Dot Product between the plane normal and the center of the Axis Aligned Box
    // using absolute values
    float fRadius = abs(N.x*E.x) + abs(N.y*E.y) + abs(N.z*E.z);
 
    Sphere sphere;
    sphere.m_Center = center;
    sphere.m_Radius = fRadius;
 
    return SphereToPlaneCollision( plane,sphere );
}

*/

bool roomEntity::collides(entity *e) {
	poly_list polys=this->model->getPolys();
	for (unsigned int i=0; i<polys.size(); i++) {
		
	}
	return false;

}