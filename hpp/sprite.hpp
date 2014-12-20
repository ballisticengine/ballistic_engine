

#ifndef SPRITE_HPP
#define	SPRITE_HPP

#include "entity.hpp"
#include "texturable.hpp"

class Sprite : public entity,public Texturable {
public:
	Sprite();
	Sprite(string file);
	e_loc width;
	e_loc height;
};


#endif	/* SPRITE_HPP */

