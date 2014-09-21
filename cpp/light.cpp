#include "light.hpp"


void light::setAmbient(const colorRGBA &color) {
 this->ambient=color;
}

void light::setDiffuse(const colorRGBA &color) {
this->diffuse=color;
}

void light::setSpecular(const colorRGBA &color) {
this->specular=color;
}

void light::setAllColors(const colorRGBA &color) {
	this->setAmbient(color);
	this->setDiffuse(color);
	this->setSpecular(color);
}

colorRGBA light::getAmbient() {
	return this->ambient;
}

colorRGBA light::getDiffuse() {
	return this->diffuse;
}

colorRGBA light::getSpecular() {
	return this->specular;
}