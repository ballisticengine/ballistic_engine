

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
        Sprite(Ballistic::Types::Texture *tex,scalar_t w,scalar_t h);
	scalar_t width;
	scalar_t height;
	Shape2d *shape;
};


#endif	

