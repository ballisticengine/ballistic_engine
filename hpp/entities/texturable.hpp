#ifndef TEXTURABLE_H
#define TEXTURABLE_H

#include "types/texture.hpp"


class Texturable {
	
public:
	Texture *tex;
	virtual void setTexture(Texture *tex);
	virtual Texture * getTexture();
};



#endif