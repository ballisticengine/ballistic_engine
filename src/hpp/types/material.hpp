#ifndef MATERIAL_H
#define MATERIAL_H


#include "types/types.hpp"
#include "types/texture.hpp"
#include "types/lightOrMaterial.hpp"


class Material : public LightOrMaterial {
protected:
	//colorRGBA emission,shininess;
	e_loc emission,shininess;
	Texture *tex;
public:
	Material();
	void setEmission(e_loc e);
	void setShininess(e_loc s);
	e_loc getEmission();
	e_loc getShininess();

};



#endif