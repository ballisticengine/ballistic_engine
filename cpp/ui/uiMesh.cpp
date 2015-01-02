#include "ui/uiMesh.hpp"

UiMesh::UiMesh(string model,e_loc x,e_loc y,e_loc z) {
    this->model=(faceTexShape *)shapeFactory::getInstance()->get(model);

    this->x=x; this->y=y; this->z=z;
}
