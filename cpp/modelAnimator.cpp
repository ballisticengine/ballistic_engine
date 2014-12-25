#include "modelAnimator.hpp"

void ModelAnimator::animate() {
	//cout << "SS: " << shapes.size() << endl;
	for(size_t i=0; i<shapes.size(); i++) {

		
		shapes[i]->vertices=states[i].current_vertices;//shapes[i]->frames[states[i].current_frame].verts;
		for(size_t vi=0; vi<shapes[i]->v_count; vi++) {
		 size_t next_key=states[i].current_keyframe+1,current_key=states[i].current_keyframe;
		 MathTypes::vector s(shapes[i]->frames[current_key].verts[vi]),e(shapes[i]->frames[next_key].verts[vi]),r,diff,
			 base(shapes[i]->frames[0].verts[vi]);
		 
		 diff=e-base;
		 diff=diff*states[i].interpol;
		 r=s+diff;
		 states[i].current_vertices[vi].x=r.x;
		 states[i].current_vertices[vi].y=r.y;
		 states[i].current_vertices[vi].z=r.z;
		}
		states[i].interpol+=0.1;
		if(states[i].interpol>1) {
			states[i].interpol=0;
			states[i].current_keyframe++;
		}
		//states[i].current_frame++;
		if(states[i].current_keyframe==shapes[i]->frame_count-1) {
			states[i].current_keyframe=0;
		}
		
		SDL_Delay(100);
	}
}

void ModelAnimator::addShape(shape *s) {
	cout << "Frame count: " << s->frame_count << endl;
	this->shapes.push_back(s);
	ShapeState state;
	state.current_keyframe=0;
	state.interpol=0;
	state.current_vertices=new v_type[s->v_count];
	for(size_t i=0; i<s->v_count; i++) {
		state.current_vertices[i]=s->vertices[i];
	}
	states.push_back(state);
}