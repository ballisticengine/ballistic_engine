#include "roomEntity.hpp"


roomEntity::roomEntity() {

}

MathTypes::vector roomEntity::collides(BoundingCube *bound,coords offset) {

	e_loc in_count,out_count;
	in_count=out_count=0;
	BoundingCube bound2=*bound;
	MathTypes::vector tmp;
	
	bound2.max=bound->min;
	bound2.min=bound->max;
	MathTypes::vector cvec,cres,none,am,bm;
	//cout << "D" << a->width << endl;
	
	for(size_t i=0; i<boundings.size(); i++) {
		bool col=hitTest(boundings[i],bound,offset.translation);
		if(col) {
			in_count++;
		} else {
			
			am.x=boundings[i]->min.x+boundings[i]->width/2;
			am.y=boundings[i]->min.y+boundings[i]->height/2;
			am.z=boundings[i]->min.z+boundings[i]->depth/2;
			bm.x=bound->min.x+bound->width/2;
			bm.y=bound->min.y+bound->height/2;
			bm.z=bound->min.z+bound->depth/2;
			e_loc halfw=boundings[i]->width/2+bound->width/2,
			halfh=boundings[i]->height/2+bound->height/2,
			halfd=boundings[i]->depth/2+bound->depth/2;
			e_loc xAxis=abs(bm.x-am.x),
					zAxis=abs(bm.z-am.z),
					yAxis=abs(bm.y-am.y),
					xdif=xAxis-halfw,
					zdif=zAxis-halfd,
					ox=abs(xdif),
					oz=abs(zdif),
					oy=abs(yAxis-halfh)
				;
			
			if(ox>oz) {
				e_loc dif=am.z-bm.z;
				if(dif>0)
					cvec.x=bound->width/2;
				else cvec.x=-bound->width/2;
			}
			if(oz>ox) {
			e_loc dif=am.x-bm.x;

			if(dif>0) 
			 cvec.z=bound->depth/2;
			else
				cvec.z=-bound->depth/2;
			
			}
			out_count++;
		}
	}
	//cout << in_count << ", " << out_count << endl;
	if(out_count==1) {
		//cvec.write();
		return cvec;
	}
	/*for(size_t i=0; i<boundings.size(); i++) {
		cres=collisionTest(boundings[i],&bound2,offset);
		if (cres.x || cres.y || cres.z) {
			in_count++;
		} else {
		 out_count++;
		 cvec=cvec+cres;
		}
	}

	
	if(out_count!=0) { //lub ==0
		cvec.write();
		return cvec;
	}
	*/
	return none;
}
	




