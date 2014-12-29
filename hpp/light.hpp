/* 
 * File:   light.hpp
 * Author: maciek
 *
 * Created on June 23, 2014, 8:53 PM
 */

#ifndef LIGHT_HPP
#define	LIGHT_HPP

#include "entity.hpp"
#include "types.hpp"


/*
Wsp�lne w�a�ciwo�ci dla materia��w i �wiate�
*/
class LightOrMaterial {
protected:
	colorRGBA ambient,diffuse,specular;
public:
	virtual colorRGBA getAmbient();
	virtual colorRGBA getDiffuse();
	virtual colorRGBA getSpecular();
	virtual void setAmbient(const colorRGBA &color);
	virtual void setDiffuse(const colorRGBA &color);
	virtual void setSpecular(const colorRGBA &color);
	virtual void setAllColors(const colorRGBA &color);
};

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

