#ifndef TEXTURABLE_H
#define TEXTURABLE_H

#include "texture.hpp"


class Texturable {
protected:	
	texture *tex;
public:
	virtual void setTexture(texture *tex);
	virtual texture * getTexture();
};



#endif