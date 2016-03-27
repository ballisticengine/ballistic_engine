#include "entities/light.hpp"

#ifndef POINTLIGHT_HPP
#define	POINTLIGHT_HPP

/**
�wiat�o punktowe
*/
class PointLight : public Light {
public:
	LightType getType();
};

#endif