#include "roomEntity.hpp"


roomEntity::roomEntity() {

}
	
shape *roomEntity::getBoundingShape() {
	return this->model;
}

/*


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

int SphereToPlaneCollision(const Plane& plane, const Sphere& sphere)
{
    float dot = dot_product(plane.normal,sphere.m_Center) - plane.offset;
 
    if(dot > sphere.m_Radius)
        return 1; // The sphere is in front of the plane
    else if(dot < -sphere.m_Radius)
        return 2; // The sphere is behind the plane
 
    return 3; // The sphere collides/straddles with the plane
}

*/

bool roomEntity::collides(entity *e) {
	poly_list polys=this->model->getPolys();
	for (unsigned int i=0; i<polys.size(); i++) {
		BoundingCube *bound=e->getBoundingBox();
		vertex *v=polys[i]->v[0];
		MathTypes::vector max,min;
		coords c=e->getCoords();
		max.x=bound->max.x+c.x;
		max.y+=bound->max.y+c.y;
		max.z+=bound->max.z+c.z;
		min.x+=bound->min.x+c.x;
		min.y+=bound->min.y+c.y;
		min.z+=bound->min.z+c.z;
		MathTypes::vector E;
		E=(max-min);
		E.x/=2;
		E.y/=2;
		E.z/=2;
		MathTypes::vector center=min+E;
		e_loc radius=abs(v->normal.x*E.x)+abs(v->normal.y*E.y)+abs(v->normal.z*E.z);
		e_loc dot = v->normal.dotProduct(&center);
		//E.write();
		//center.write();
		//v->normal.write();
		//cout << radius << endl;
		if(dot > radius) {
        cout << "The sphere is in front of the plane" << endl;
		} else if(dot < -radius) {
        cout << "The sphere is behind the plane" << endl;
		} else {
			cout << "The sphere collides/straddles with the plane" << endl;
			return true;
		}

	}
	return false;

}