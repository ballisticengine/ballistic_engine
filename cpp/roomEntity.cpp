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
	MathTypes::vector cvec,cres,none;
	for(size_t i=0; i<boundings.size(); i++) {
		cres=collisionTest(boundings[i],&bound2,offset);
		if (cres.x || cres.y || cres.z) {
			in_count++;
		} else {
		 out_count++;
		 cvec=cvec+cres;
		}
	}

	//cout << in_count << ", " << out_count << endl;
	if(out_count!=0) { //lub ==0
		cvec.write();
		return cvec;
	}
	
	return none;
}
	




