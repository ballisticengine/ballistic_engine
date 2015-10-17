#include "types/types.hpp"



void Coords::reset() {
    translation.x =  translation.z = translation.y = rotation.x = rotation.y = rotation.z = 0; //t.y =
}

Coords::Coords() {
    this->reset();
}

ColorRGB::ColorRGB(unsigned int i) {
    //int x = (number >> (8*n)) & 0xff
    int x = 
    r = ((unsigned char *)(&i))[2]; ///255;
    g = ((unsigned char *)(&i))[1]; ///255;
    b = ((unsigned char *)(&i))[0]; ///255;
    
    
}

ColorRGB::ColorRGB(e_loc r, e_loc g,e_loc b) : r(r), g(b), b(b) {
    
}

bool ColorRGB::operator=(const ColorRGB &color) {
    return (r==color.r && g==color.g && b==color.b);
}

////////////

ColorRGBA::ColorRGBA(e_loc r, e_loc g,e_loc b, e_loc a) :ColorRGB(r,g,b), a(a) {
}

bool ColorRGBA::operator=(const ColorRGBA &color) {
    return (r==color.r && g==color.g && b==color.b && a==color.a);
}

ColorRGBA::ColorRGBA(unsigned int i) : ColorRGB(i) {
    
    a = 1;
}