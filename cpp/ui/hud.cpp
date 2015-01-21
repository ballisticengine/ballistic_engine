#include "ui/hud.hpp"


void HUD::addImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y) {
  UiImage *img=new UiImage(fn,name,width,height,x,y);
  this->images.push_back(img);  
  this->images_mapped[name]=img;
}

UiImage *HUD::getImage(string name) {
    return this->images_mapped[name];
}

image_list HUD::getImages() {
 return this->images;   
}

HUD::HUD() {
    
}

HUD::~HUD() {
    deleteVector(this->images);
}