#include "roomEntity.hpp"


roomEntity::roomEntity() {

}

bool roomEntity::collides(BoundingCube *bound) {

	e_loc in_count,out_count;
	in_count=out_count=0;
	for(size_t i=0; i<boundings.size(); i++) {
		if (!collisionTest(bound,boundings[i])) {
			in_count++;
		} else {
		 out_count++;
		}
	}

	if(out_count==0) {
	 return true;
	}
	//cout << in_count << ", " << out_count << endl;
	return false;
}
	




