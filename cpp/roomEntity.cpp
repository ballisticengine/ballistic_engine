#include "roomEntity.hpp"


roomEntity::roomEntity() {

}
	
shape *roomEntity::getBoundingShape() {
	return this->model;
}

bool roomEntity::collides(entity *e,coords offset) {
	//coords c=e->getCoords();
	vert_list vs=this->model->getVertices();
	cout << vs.size() << "X" << endl;
	for(int i=0; i<vs.size(); i++) {
		
	}
	return false;
 
}