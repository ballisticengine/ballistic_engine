

#ifndef SPRITE_HPP
#define	SPRITE_HPP

#include "entities/entity.hpp"
#include "entities/texturable.hpp"
#include "factories/textureFactory.hpp"
#include "types/texture.hpp"

#include "types/shape2d.hpp"

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

