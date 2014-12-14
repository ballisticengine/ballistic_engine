#include "entity.hpp"


coords entity::getCoords() {
	coords c;
	c.translation.x=x;
	c.translation.y=y;
	c.translation.z=z;
	c.rotation.x=rx;
	c.rotation.y=ry;
	c.rotation.z=rz;
	return c;
}

void entity::translate(e_loc x,e_loc y,e_loc z) {
 this->x+=x;
 this->y+=y;
 this->z+=z;
 if(this->bounding_box) {
	 this->bounding_box->max.x+=x;
	 this->bounding_box->max.y+=y;
	 this->bounding_box->max.z+=z;
	 this->bounding_box->min.x+=x;
	 this->bounding_box->min.y+=y;
	 this->bounding_box->min.z+=z;
	 this->bounding_box->loc.x=this->x;
	 this->bounding_box->loc.y=this->y;
	 this->bounding_box->loc.z=this->z;
 }
}

void entity::rotate(e_loc x,e_loc y, e_loc z) {
 this->rx+=x;
 this->ry+=y;
 this->rz+=z;
}

void entity::locate(e_loc x,e_loc y,e_loc z) {
 this->x=x;
 this->y=y;
 this->z=z;


}

void entity::face(e_loc x,e_loc y,e_loc z) {
 this->rx=x;
 this->ry=y;
 this->rz=z;
}

void entity::translate(coords c) {
	this->translate(c.translation.x,c.translation.y,c.translation.z);
}

entity::entity() {
 
}

/* offset to w³aœciwie nowa pozycja, a nie przemieszczenie */

MathTypes::vector entity::collides(BoundingCube *bound,coords offset) 

{
	
	return collisionTest(this->bounding_box,bound,offset);
	
}

void entity::setBoundingBox(BoundingCube *box) {
	this->bounding_box=box;
	bounding_box->max.x-=x;
	bounding_box->max.y-=y;
	bounding_box->max.z-=z;
	
	bounding_box->min.x-=x;
	bounding_box->min.y-=y;
	bounding_box->min.z-=z;
}

BoundingCube * entity::getBoundingBox() {
	return this->bounding_box;
}

void entity::makeBoundingBox() {
	///
}

bool hitTest(BoundingCube *a,BoundingCube *b,MathTypes::vector offset) {
	MathTypes::vector amax,amin,bmax,bmin;
	amax=a->max+offset;
	amin=a->min+offset;
	bmax=b->max+offset;
	bmin=b->min+offset;
	
	//offset.write();

	bool collide=(
		amax.x > bmin.x && 
		 amin.x < bmax.x &&
		amax.y > bmin.y &&
		 amin.y < bmax.y &&
		 amax.z > bmin.z &&
		amin.z < bmax.z
		);
	return collide;
}

MathTypes::vector collisionTest(BoundingCube *a,BoundingCube *b,coords offset) {

	
	
	MathTypes::vector res,offsetx=offset.translation,offsety=offset.translation,offsetz=offset.translation;
	
	offsetx.y=offsetx.z=0;
	offsety.x=offsety.z=0;
	offsetz.x=offsetz.y=0;



	res.x=res.y=res.z=0;

	bool col=hitTest(a,b,offset.translation);
	
	

	/*
	
	 return oldBoxRight < otherObj.Left && // was not colliding
           boxRight >= otherObj.Left;
	*/


	e_loc 
		
		aright=a->max.x+a->width,//+offset.translation.x,
		aleft=a->min.x,//+offset.translation.x
		afront=a->min.z,
		aback=a->max.z+a->depth,
		
		bleft=b->min.x,
		bright=b->max.x+b->width,
		bfront=b->min.z,
		bback=b->max.z+b->depth,
		halfw=a->width/2+b->width/2,
		halfh=a->height/2+b->height/2,
	halfd=a->depth/2+b->depth/2;
	

	MathTypes::vector am,bm;
	//cout << "D" << a->width << endl;
	am.x=a->min.x+a->width/2;
	am.y=a->min.y+a->height/2;
	am.z=a->min.z+a->depth/2;

	bm.x=b->min.x+b->width/2;
	bm.y=b->min.y+b->height/2;
	bm.z=b->min.z+b->depth/2;
	e_loc xAxis=abs(bm.x-am.x),
		zAxis=abs(bm.z-am.z),
		yAxis=abs(bm.y-am.y),
		xdif=xAxis-halfw,
		zdif=zAxis-halfd,
		ox=abs(xdif),
		oz=abs(zdif),
		oy=abs(yAxis-halfh)
		;

	//cout << bleft << ", " << aleft << "|" << bright << ", " << bleft << endl;
	if(!col) {
	 return res;
	}
	
	if(ox>oz) {
	 res.x=xdif; //tu dodaæ stronê (prawa/lewa)
	}


	


	if(0) { //todo
	 res.y=1;//am.y-bm.y;
	}

	if(oz>ox) {
	 res.z=zdif;//am.z-bm.z;
	}

	res.write();
	return res;
}