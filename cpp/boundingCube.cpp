#include "boundingCube.hpp"

BoundingCube::BoundingCube() {
	
}

BoundingCube::BoundingCube(shape *s) {
	this->calculate(s);
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

*/

e_loc BoundingCube::toSphereRadius() {
	MathTypes::vector E=(max-min)/2.0f;	
	MathTypes::vector center=min+E;
	
	return 0;
}

BoundingCube::BoundingCube(e_loc width,e_loc height,e_loc depth) {
	this->width=width;
	this->height=height;
	this->depth=depth;
	max.x=width/2;
	min.x=-width/2;
	max.y=height/2;
	min.y=-height/2;
	max.z=depth/2;
	min.z=-depth/2;
}

void BoundingCube::calculate(shape *s) {
vert_list vs=s->getVertices();
	//e_loc max_x,min_x,max_y,min_y,max_z,min_z;
	max.x=min.x=max.y=min.y=max.z=min.z=0;
	
	for (unsigned int i=0; i<vs.size(); i++) {
		if (vs[i]->x > max.x) {
			max.x=vs[i]->x;
		}

		if(vs[i]->x < min.x) {
		 min.x=vs[i]->x;
		}

		if (vs[i]->y > max.y) {
			max.y=vs[i]->y;
		}

		if(vs[i]->y < min.y) {
		 min.y=vs[i]->y;
		}

		if (vs[i]->z > max.z) {
			max.z=vs[i]->z;
		}

		if(vs[i]->z < min.z) {
		 min.z=vs[i]->z;
		}

		cout << vs[i]->x << ", ";
	}

	this->width=max.x-min.x;
	this->height=max.y-min.y;
	this->depth=max.z-min.z;
}

e_loc BoundingCube::getWidth() {
	return this->width;
}

e_loc BoundingCube::getHeight() {
	return this->height;
}

e_loc BoundingCube::getDepth() {
	return this->depth;
}

void BoundingCube::print() {
// cout << "Max x " << max_x << "|" << "Min y " << min_y << 
}