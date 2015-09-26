

#ifndef SPRITE_HPP
#define	SPRITE_HPP

#include "entities/entity.hpp"
#include "entities/texturable.hpp"

#include "types/texture.hpp"

#include "types/shape2d.hpp"

class Sprite : public Entity,public Texturable {
protected:
	virtual void setUp();
public:
	Sprite();
	Sprite(Ballistic::Types::Texture *tex);
        Sprite(Ballistic::Types::Texture *tex,e_loc w,e_loc h);
	e_loc width;
	e_loc height;
	Shape2d *shape;
};


#endif	

