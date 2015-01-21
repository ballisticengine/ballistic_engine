#ifndef LIGHTORMATERIAL_HPP
#define	LIGHTORMATERIAL_HPP

#include "types/types.hpp"

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

#endif

