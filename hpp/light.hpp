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

class light : public entity {
protected:
	colorRGBA ambient,diffuse,specular;

public:
	colorRGBA getAmbient();
	colorRGBA getDiffuse();
	colorRGBA getSpecular();
	void setAmbient(const colorRGBA &color);
	void setDiffues(const colorRGBA &color);
	void setSpecular(const colorRGBA &color);
	void setAllColors(const colorRGBA &color);
};

#endif	/* LIGHT_HPP */

