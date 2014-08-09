#include "camera.hpp"

camera::camera() {
}

camera::camera(frustumSizes frustum) {
	this->setFrustum(frustum);
}

void camera::setFrustum(frustumSizes frustum) {
 this->frustum=frustum;
}

frustumSizes camera::getFrustum() {
 return this->frustum;
}