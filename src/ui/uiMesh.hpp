#ifndef UIMESH_HPP
#define	UIMESH_HPP

#include <string>
#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"
#include "entities/texturable.hpp"
#include "resources/ResourceManager.hpp"


using namespace std;

class UiMesh  {
   
public:
    Shape *model;
    Coords c;
    scalar_t scale;
    UiMesh(string model,scalar_t x,scalar_t y,scalar_t z);
};

#endif	
