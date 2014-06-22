#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include "singleton.hpp"

struct videoData {
    int width,height,bpp;
    
};

class renderer : public singleton {
protected:
    videoData vd;
public:
    renderer();
//    virtual void test();
    
    
    void init(videoData vd);
    virtual void specificInit() {
        
    };
    
    virtual void render()=0;
    
    virtual ~renderer();
};


#endif	/* RENDERERABSTRACT_HPP */

