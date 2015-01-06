#ifndef UIMESH_HPP
#define	UIMESH_HPP

#include <string>
#include "types/types.hpp"

#include "types/texture.hpp"
#include "entities/texturable.hpp"
#include "factories/shapeFactory.hpp"
#include "factories/textureFactory.hpp"

using namespace std;

class UiMesh  {
   
public:
    shape *model;
    coords c;
    e_loc scale;
    UiMesh(string model,e_loc x,e_loc y,e_loc z);
};

#endif	
