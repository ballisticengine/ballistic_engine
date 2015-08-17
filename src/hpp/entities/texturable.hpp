#ifndef TEXTURABLE_H
#define TEXTURABLE_H

#include "types/texture.hpp"


class Texturable {
	
public:
	Ballistic::Types::Texture *tex;
	virtual void setTexture(Ballistic::Types::Texture *tex);
	virtual Ballistic::Types::Texture * getTexture();
};



#endif