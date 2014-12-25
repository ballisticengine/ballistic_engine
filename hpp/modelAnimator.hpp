#ifndef MODELANIMATOR_H
#define MODELANIMATOR_H

#include <iostream>
using namespace std;
#include <SDL/SDL.h>

#include "animator.hpp"
#include "types.hpp"
#include "timer.hpp"

struct ShapeState {
 size_t current_keyframe;
 e_loc interpol;
 v_type *current_vertices;
 Timer start_time,end_time;
};

class ModelAnimator : public Animator {
protected:
	virtual void animate();
	shape_list shapes;
	vector <ShapeState> states;

public:
	void addShape(shape *s);


};

#endif