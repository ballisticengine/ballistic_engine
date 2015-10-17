#include <limits.h>
#include <gtest/gtest.h>

#include "types/types.hpp"

TEST(TypesTest, Colors) {
    unsigned int 
        red_rgb = 0xff0000
    ;
    ColorRGB c_rgb(red_rgb);
    ColorRGBA c_rgba(red_rgb);
    
    cout << "C_RGB " << c_rgb.r << ", " << c_rgb.g << ", " << c_rgb.b << ", " << endl;
    cout << "C_RGBA " << c_rgba.r << ", " << c_rgba.g << ", " << c_rgba.b << ", " << c_rgba.a  << endl;
};
