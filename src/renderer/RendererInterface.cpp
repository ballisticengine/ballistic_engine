#include "renderer/RendererInterface.hpp"

void RendererInterface::face(Vector3d &v) {
    this->rotate(Vector3d(1, 0, 0), v.x);
    this->rotate(Vector3d(0, 1, 0), v.y);
    this->rotate(Vector3d(0, 0, 1), v.z);
}
