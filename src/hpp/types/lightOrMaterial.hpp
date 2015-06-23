#ifndef LIGHTORMATERIAL_HPP
#define	LIGHTORMATERIAL_HPP

#include "types/types.hpp"

/*
Wsp�lne w�a�ciwo�ci dla materia��w i �wiate�
*/
class LightOrMaterial {
protected:
	ColorRGBA ambient,diffuse,specular;
public:
	virtual ColorRGBA getAmbient();
	virtual ColorRGBA getDiffuse();
	virtual ColorRGBA getSpecular();
	virtual void setAmbient(const ColorRGBA &color);
	virtual void setDiffuse(const ColorRGBA &color);
	virtual void setSpecular(const ColorRGBA &color);
	virtual void setAllColors(const ColorRGBA &color);
};

#endif

