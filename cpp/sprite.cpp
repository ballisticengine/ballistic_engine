#include "sprite.hpp"

void Sprite::setUp() {
videoData *vd=config::getInstance()->getVD();

	this->width=(e_loc)this->tex->getWidth()/vd->width;
	this->height=(e_loc)this->tex->getHeight()/vd->height;
	this->shape=new Shape2d(this->width,this->height);
}

Sprite::Sprite() {
	
}

Sprite::Sprite(texture *tex) {
 this->tex=tex;
 this->setUp();
}

Sprite::Sprite(string file) {
	this->tex=(texture *)textureFactory::getInstance()->get(file);
	this->setUp();
}