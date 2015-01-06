/* 
 * File:   light.hpp
 * Author: maciek
 *
 * Created on June 23, 2014, 8:53 PM
 */

#ifndef LIGHT_HPP
#define	LIGHT_HPP

#include "entities/entity.hpp"
#include "types/types.hpp"
#include "types/lightOrMaterial.hpp"




/* rodzaj �wiat�a zwracany przez funckj� light::getType() */
typedef enum  {
 POINTLIGHT,
 SPOTLIGHT,
 SUNLIGHT
}  LightType ;

/**
* Abstrakcyjna klasa opisuj�ca �wiat�o
*/
class light : public entity,public LightOrMaterial {
protected:
	colorRGBA ambient,diffuse,specular;

public:
	
	virtual  LightType getType()=0;
};

#endif	/* LIGHT_HPP */

