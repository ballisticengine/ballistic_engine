#include "ui/uiMesh.hpp"

UiMesh::UiMesh(string model,scalar_t x,scalar_t y,scalar_t z) {
//    this->model=ShapeFactory::getInstance()->getShape(model);

    this->c.translation.x=x; this->c.translation.y=y; this->c.translation.z=z;
}
