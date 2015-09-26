#ifndef Camera_H
#define Camera_H

#include "types/types.hpp"
#include "entities/entity.hpp"
#include "config/Config.hpp"

class Camera : public Entity {
protected:
	FrustumSizes frustum;
public:
	Camera();
	Camera(FrustumSizes frustum);
	void setFrustum(FrustumSizes frustum);
	FrustumSizes getFrustum();


};

#endif