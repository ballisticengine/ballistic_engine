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

/* rodzaj œwiat³a zwracany przez funckjê light::getType() */
enum LightType {
 POINTLIGHT,
 SPOTLIGHT,
 SUNLIGHT
}  ;

/**
* Abstrakcyjna klasa opisuj¹ca œwiat³o
*/
class light : public entity {
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
	virtual  LightType getType()=0;
};

#endif	/* LIGHT_HPP */

