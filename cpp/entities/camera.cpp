#include "entities/Camera.hpp"

Camera::Camera() {
}

Camera::Camera(FrustumSizes frustum) {
	this->setFrustum(frustum);
}

void Camera::setFrustum(FrustumSizes frustum) {
 this->frustum=frustum;
}

FrustumSizes Camera::getFrustum() {
 return this->frustum;
}