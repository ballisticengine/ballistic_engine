#ifndef TEXTURABLE_H
#define TEXTURABLE_H

#include "texture.hpp"


class Texturable {
	
public:
	texture *tex;
	virtual void setTexture(texture *tex);
	virtual texture * getTexture();
};



#endif