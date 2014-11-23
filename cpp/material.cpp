#include "material.hpp"

void Material::setEmission(e_loc e) {
	this->emission=e;
}

void Material::setShininess(e_loc s) {
	this->shininess=s;
}

e_loc Material::getEmission() {
	return this->emission;
}

e_loc Material::getShininess() {
	return this->shininess;
}



Material::Material() {
}