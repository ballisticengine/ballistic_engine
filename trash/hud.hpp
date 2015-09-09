#ifndef HUD_HPP
#define	HUD_HPP

#include "misc/singleton.hpp"
#include "misc/utils.hpp"
#include "ui/image.hpp"
#include "ui/uiMesh.hpp"
#include "types/types.hpp"

class HUD : public Singleton<HUD> {
protected:
        image_list images; //tu zrobić mapę a nie vector
        image_map images_mapped;
public:
    virtual void addImage(string fn,string name,e_loc width,e_loc height,e_loc x,e_loc y);
    virtual UiImage *getImage(string name);
    UiMesh *mesh;
    virtual image_list getImages();
    HUD();
    virtual ~HUD();
};

#endif	

