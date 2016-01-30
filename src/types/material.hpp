#ifndef MATERIAL_H
#define MATERIAL_H


#include "types/types.hpp"
#include "types/texture.hpp"
#include "types/lightOrMaterial.hpp"


class Material : public LightOrMaterial {
protected:
	//colorRGBA emission,shininess;
	scalar_t emission,shininess;
	Ballistic::Types::Texture *tex;
public:
	Material();
	void setEmission(scalar_t e);
	void setShininess(scalar_t s);
	scalar_t getEmission();
	scalar_t getShininess();

};



#endif