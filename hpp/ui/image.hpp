#ifndef IMAGE_HPP
#define	IMAGE_HPP

#include <vector>
#include <map>
#include "types/types.hpp"
#include "types/shape.hpp"
#include "types/shape2d.hpp"
#include "types/texture.hpp"
#include "entities/texturable.hpp"
#include "factories/textureFactory.hpp"
//#include "config/config.hpp"

using namespace std;

enum IMAGE_POSITION_H {
    CENTER,
    LEFT,
    RIGHT
};

enum IMAGE_POSITION_V {
    TOP,
    BOTTOM,
    MIDDLE
};

class UiImage : public Texturable {
protected:
    IMAGE_POSITION_H h;
    IMAGE_POSITION_V v;
    
public:
    string name;
    Shape2d *shape;
    e_loc x,y; //Width i height w shape2d
    UiImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y);
    UiImage();
    ~UiImage();
    void setText();
    
    virtual void position(IMAGE_POSITION_H h,IMAGE_POSITION_V v);
    virtual IMAGE_POSITION_H getPositionH();
    virtual IMAGE_POSITION_V getPositionV();
};

typedef vector<UiImage *> image_list;
typedef map<string,UiImage *> image_map;


#endif	

