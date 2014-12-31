#ifndef HUD_HPP
#define	HUD_HPP

#include "misc/singleton.hpp"
#include "misc/utils.hpp"
#include "ui/image.hpp"

class HUD : public singleton<HUD> {
protected:
        image_list images; //tu zrobić mapę a nie vector
public:
    virtual void addImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y);
    virtual image_list getImages();
    HUD();
    virtual ~HUD();
};

#endif	

