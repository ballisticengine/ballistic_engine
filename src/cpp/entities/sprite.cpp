#include "entities/sprite.hpp"

void Sprite::setUp() {
    //videoData *vd=Config::getInstance()->getVD();

    //this->width=((e_loc)this->tex->getWidth()/vd->width)*5;
    //this->height=((e_loc)this->tex->getHeight()/vd->height)*5;
    if (this->width == 0 || this->height == 0) {
        this->width = 10;
        this->height = 10;
    }

    this->shape = new Shape2d(this->width, this->height);
}

Sprite::Sprite() {

}

Sprite::Sprite(Texture *tex) {
    this->tex = tex;
    this->setUp();
}

Sprite::Sprite(Texture *tex,e_loc w,e_loc h) {
     this->width=w;
     this->height=h;
     this->tex=tex;
     this->setUp();
 }

