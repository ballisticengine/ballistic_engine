#include "types/lightOrMaterial.hpp"

void LightOrMaterial::setAmbient(const colorRGBA &color) {
 this->ambient=color;
}

void LightOrMaterial::setDiffuse(const colorRGBA &color) {
this->diffuse=color;
}

void LightOrMaterial::setSpecular(const colorRGBA &color) {
this->specular=color;
}

void LightOrMaterial::setAllColors(const colorRGBA &color) {
	this->setAmbient(color);
	this->setDiffuse(color);
	this->setSpecular(color);
}

colorRGBA LightOrMaterial::getAmbient() {
	return this->ambient;
}

colorRGBA LightOrMaterial::getDiffuse() {
	return this->diffuse;
}

colorRGBA LightOrMaterial::getSpecular() {
	return this->specular;
}
