#include "types/material.hpp"

void Material::setEmission(scalar_t e) {
	this->emission=e;
}

void Material::setShininess(scalar_t s) {
	this->shininess=s;
}

scalar_t Material::getEmission() {
	return this->emission;
}

scalar_t Material::getShininess() {
	return this->shininess;
}



Material::Material() {
}