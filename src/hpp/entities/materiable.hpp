#ifndef MATERIABLE_H
#define MATERIABLE_H

#include "entities/texturable.hpp"
#include "types/material.hpp"

class Materiable : public Texturable {
protected:
	Material *mat;
public:
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
};
#endif