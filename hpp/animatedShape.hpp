#ifndef ANIMATEDSHAPE_H
#define ANIMATEDSHAPE_H

#include "types.hpp"

class AnimatedShape : public shape {
public:
	size_t frame_count;
	v_type **frames;
};

#endif