#include "ui/uiMesh.hpp"

UiMesh::UiMesh(string model,e_loc x,e_loc y,e_loc z) {
    this->model=ShapeFactory::getInstance()->getShape(model);

    this->c.translation.x=x; this->c.translation.y=y; this->c.translation.z=z;
}
