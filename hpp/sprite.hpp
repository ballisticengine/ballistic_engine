

#ifndef SPRITE_HPP
#define	SPRITE_HPP

#include "entity.hpp"
#include "texturable.hpp"
#include "textureFactory.hpp"
#include "texture.hpp"
#include "config.hpp"
#include "shape2d.hpp"

class Sprite : public entity,public Texturable {
protected:
	virtual void setUp();
public:
	Sprite();
	Sprite(string file);
	Sprite(texture *tex);
	e_loc width;
	e_loc height;
	Shape2d *shape;
};


#endif	

