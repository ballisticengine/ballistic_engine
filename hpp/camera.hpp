#ifndef CAMERA_H
#define CAMERA_H

#include "types.hpp"
#include "entity.hpp"

class camera : public entity {
protected:
	frustum_sizes frustum;

}

#endif