#include "mathTypes.hpp"

e_loc normalizeRotation(e_loc r) {
	e_loc ra=abs(r);	
	e_loc rmod=fmod(ra,360);
	if(r>=0) {
	 r=rmod;
	} else {
	 r=-rmod;
	}
	return r;
}


namespace MathTypes {

vector::vector() {
 x=y=z=0;
}

}