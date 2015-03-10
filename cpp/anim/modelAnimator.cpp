#include "anim/modelAnimator.hpp"

void ModelAnimator::animate() {
	//cout << "SS: " << shapes.size() << endl;
	for(size_t i=0; i<shapes.size(); i++) {

		
		shapes[i]->vertices=states[i].current_vertices;//shapes[i]->frames[states[i].current_frame].verts;
		 size_t next_key=states[i].current_keyframe+1,current_key=states[i].current_keyframe;
		for(size_t vi=0; vi<shapes[i]->v_count; vi++) {
		
		 MathTypes::Vector3d s(shapes[i]->frames[current_key].verts[vi]),e(shapes[i]->frames[next_key].verts[vi]),r,diff,
			 base(shapes[i]->frames[0].verts[vi]);
		 
		 diff=e-base;
		 diff=diff*states[i].interpol;
		 r=s+diff;
		 states[i].current_vertices[vi].x=r.x;
		 states[i].current_vertices[vi].y=r.y;
		 states[i].current_vertices[vi].z=r.z;
		}
		e_loc tdiff=states[i].end_time.getDiffNR();
				e_loc ratio=tdiff/shapes[i]->frame_times[next_key];
		//cout << tdiff << ", " << shapes[i]->frame_times[states[i].current_keyframe] << endl;
		states[i].interpol=ratio;
		//cout << tdiff << ", " << ratio << ", " << states[i].interpol << ", " << shapes[i]->frame_times[next_key]<< ", " <<states[i].current_keyframe << endl;
		if(states[i].interpol>=1) {
			states[i].end_time.stop();
			states[i].end_time.start();
			states[i].interpol=0;
			states[i].current_keyframe++;
		}
		//states[i].current_frame++;
		if(states[i].current_keyframe==shapes[i]->frame_count-1) {
			
			states[i].current_keyframe=0;
			
		}
		
		//SDL_Delay(100);
	}
}

void ModelAnimator::addShape(Shape *s) {
	cout << "Frame count: " << s->frame_count << endl;
	this->shapes.push_back(s);
	ShapeState state;
	state.current_keyframe=0;
	state.interpol=0;
	state.current_vertices=new v_type[s->v_count];
	state.start_time.start();
	state.end_time.start();
	for(size_t i=0; i<s->v_count; i++) {
		state.current_vertices[i]=s->vertices[i];
	}
	states.push_back(state);
}