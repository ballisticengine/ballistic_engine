#include "ui/image.hpp"

UiImage::UiImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y) {
    this->x=x; this->y=y; this->name=name;
    this->shape=new Shape2d(width,height);
    this->tex=(texture *)textureFactory::getInstance()->get(fn);
}

 UiImage::~UiImage() {
     //delete this->shape; //to robi GPF - sprawdzić
     //Do not remove texture - factory handes that
 }
 
void UiImage::position(IMAGE_POSITION_H h,IMAGE_POSITION_V v) {
    this->h=h; this->v=v;
    
}

IMAGE_POSITION_H  UiImage::getPositionH() {
    return this->h;
}

IMAGE_POSITION_V  UiImage::getPositionV() {
    return this->v;
}