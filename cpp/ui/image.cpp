#include "ui/image.hpp"

UiImage::UiImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y) {
    this->x=x; this->y=y; this->name=name;
    this->shape=new Shape2d(width,height);
    this->tex=(texture *)textureFactory::getInstance()->get(fn);
    update=true;
    ttf=TTF::getInstance();
}

UiImage::UiImage() {
    ttf=TTF::getInstance();
    update=true;
}

void UiImage::setText(string text) {
//     SDL_Color textColor = { 255, 0, 0 };
//    this->tex->surf =TTF_RenderText_Solid( sdlIO::font,text.c_str(), textColor );
//    this->tex->surf= SDL_ConvertSurfaceFormat(this->tex->surf,SDL_PIXELFORMAT_ABGR8888,0); 
//    SDL_Rect offset;
//
//    //Get offsets
//    offset.x = 0;
//    offset.y = 0; 
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