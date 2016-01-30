#include "entities/sprite.hpp"

void Sprite::setUp() {
    //videoData *vd=Config::getInstance()->getVD();

    //this->width=((scalar_t)this->tex->getWidth()/vd->width)*5;
    //this->height=((scalar_t)this->tex->getHeight()/vd->height)*5;
    if (this->width == 0 || this->height == 0) {
        this->width = 10;
        this->height = 10;
    }

    this->shape = new Shape2d(this->width, this->height);
}

Sprite::Sprite() {

}

Sprite::Sprite(Ballistic::Types::Texture *tex) {
    this->tex = tex;
    this->setUp();
}

Sprite::Sprite(Ballistic::Types::Texture *tex,scalar_t w,scalar_t h) {
     this->width=w;
     this->height=h;
     this->tex=tex;
     this->setUp();
 }

