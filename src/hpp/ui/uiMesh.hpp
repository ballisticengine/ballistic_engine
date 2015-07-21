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
    e_loc scale;
    UiMesh(string model,e_loc x,e_loc y,e_loc z);
};

#endif	
