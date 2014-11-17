#ifndef MATERIABLE_H
#define MATERIABLE_H

#include "texturable.hpp"
#include "material.hpp"

class Materiable : public Texturable {
protected:
	Material *mat;
public:
	virtual Material *getMaterial();
	virtual void setMaterial(Material *mat);
};
#endif