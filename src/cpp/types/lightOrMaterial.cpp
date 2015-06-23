#include "types/lightOrMaterial.hpp"

void LightOrMaterial::setAmbient(const ColorRGBA &color) {
 this->ambient=color;
}

void LightOrMaterial::setDiffuse(const ColorRGBA &color) {
this->diffuse=color;
}

void LightOrMaterial::setSpecular(const ColorRGBA &color) {
this->specular=color;
}

void LightOrMaterial::setAllColors(const ColorRGBA &color) {
	this->setAmbient(color);
	this->setDiffuse(color);
	this->setSpecular(color);
}

ColorRGBA LightOrMaterial::getAmbient() {
	return this->ambient;
}

ColorRGBA LightOrMaterial::getDiffuse() {
	return this->diffuse;
}

ColorRGBA LightOrMaterial::getSpecular() {
	return this->specular;
}
