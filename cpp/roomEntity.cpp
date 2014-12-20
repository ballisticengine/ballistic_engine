#include "roomEntity.hpp"


roomEntity::roomEntity() {

}

void roomEntity::addEntity(entity *e) {
	this->entities.push_back(e);
}

void roomEntity::addPhysicalEntity(PhysicalEntity *e) {
	this->phys_entities.push_back(e);
	this->addEntity(e);
}

void roomEntity::addObjectEntity(ObjectEntity *e) {
	this->models.push_back(e);

	this->addPhysicalEntity(e);
}

void roomEntity::addLightEntity(light *e) {
	this->lights.push_back(e);
	this->addEntity(e);
}

MathTypes::vector roomEntity::collides(BoundingCube *bound,coords offset) {

	e_loc in_count,out_count;
	in_count=out_count=0;
	BoundingCube bound_off=*bound,bound_current;
	MathTypes::vector tmp;

	//bound2.max=bound->min;
	//bound2.min=bound->max;
	MathTypes::vector cvec,cres,none,am,bm;
	//cout << "D" << a->width << endl;

	for(size_t i=0; i<boundings.size(); i++) {
		bool col=hitTest(boundings[i],bound,offset.translation);
		if(col) {
			in_count++;
		} else {
			bound_current=offsetBounding(boundings[i],offset);

			am.x=bound_current.min.x+bound_current.width/2;
			am.y=bound_current.min.y+bound_current.height/2;
			am.z=bound_current.min.z+bound_current.depth/2;
			bm.x=bound->min.x+bound->width/2;
			bm.y=bound->min.y+bound->height/2;
			bm.z=bound->min.z+bound->depth/2;
			e_loc halfw=bound_current.width/2+bound->width/2,
				halfh=bound_current.height/2+bound->height/2,
				halfd=bound_current.depth/2+bound->depth/2;
			e_loc xAxis=abs(bm.x-am.x),
				zAxis=abs(bm.z-am.z),
				yAxis=abs(bm.y-am.y),
				xdif=xAxis-halfw,
				zdif=zAxis-halfd,
				ox=abs(xdif),
				oz=abs(zdif),
				oy=abs(yAxis-halfh)
				;

			if(bound_current.min.y>=bound->min.y) {
				cvec.y=COLLISION_BACK;
			}

			else if(bound_current.max.y<=bound->max.y) {
				cvec.y=-COLLISION_BACK;
			}
			if(ox>oz) {
				e_loc dif=am.z-bm.z;
				if(dif>0) {
					cvec.x=COLLISION_BACK;
				} else {
					cvec.x=-COLLISION_BACK;
				}
			}
			else if(oz>ox) {
				e_loc dif=am.x-bm.x;

				if(dif>0) {
					cvec.z=COLLISION_BACK;
				}
				else {
					cvec.z=-COLLISION_BACK;
				}
			} 


			out_count++;
		}
	}
	//cout << in_count << ", " << out_count << endl;
	if(in_count==0) {
		//cvec.write();
		return cvec;

	}

	return none;
}





