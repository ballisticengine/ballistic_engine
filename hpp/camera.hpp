#ifndef CAMERA_H
#define CAMERA_H

#include "types.hpp"
#include "entity.hpp"
#include "config.hpp"

class camera : public entity {
protected:
	frustumSizes frustum;
public:
	camera();
	camera(frustumSizes frustum);
	void setFrustum(frustumSizes frustum);
	frustumSizes getFrustum();


};

#endif