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
	MathTypes::vector cvec,cres;
	for(size_t i=0; i<boundings.size(); i++) {
		cres=collisionTest(&bound2,boundings[i],offset);
		if (cres.x && cres.y && cres.z) {
			in_count++;
		} else {
		 out_count++;
		}
	}

	//cout << in_count << ", " << out_count << endl;
	if(out_count==0) {
	 //return true;
	}
	
	return cvec;
}
	




