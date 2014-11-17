#include "material.hpp"

void Material::setEmission(colorRGBA e) {
	this->emission=e;
}

void Material::setShininess(colorRGBA s) {
	this->shininess=s;
}

colorRGBA Material::getEmission() {
	return this->emission;
}

colorRGBA Material::getShininess() {
	return this->shininess;
}



Material::Material() {
}