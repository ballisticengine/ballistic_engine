#ifndef MATERIAL_H
#define MATERIAL_H

#include "light.hpp"
#include "types.hpp"

class Material : public LightOrMaterial {
protected:
	colorRGBA emission,shininess;
public:
	void setEmission(colorRGBA e);
	void setShininess(colorRGBA s);
	colorRGBA getEmission();
	colorRGBA getShininess();
};

/*
glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, &(m_Ambient.r) );
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_Diffuse.r) );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, &(m_Specular.r) );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, &(m_Emission.r) );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess );
*/

#endif