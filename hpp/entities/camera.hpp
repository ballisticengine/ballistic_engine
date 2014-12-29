#ifndef CAMERA_H
#define CAMERA_H

#include "types/types.hpp"
#include "entities/entity.hpp"
#include "config/config.hpp"

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