#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include <iostream>

using namespace std;

#include "singleton.hpp"
#include "types.hpp"
#include "texture.hpp"
#include "skybox.hpp"
#include "world.hpp"

struct videoData {
    int width,height,bpp;
    
};

typedef  void (*flushf)();

class renderer : public singleton {
protected:
    videoData vd;
    float frustum_start,frustum_end,frustum_x,frustum_y; //może jednak do GL
    flushf flush_callback;
    world *w;
    virtual void renderShape(shape *s);
    virtual void renderPShape(shape *s);
    virtual void renderVertex(vertex *v)=0;
    virtual void renderSkybox(skybox *sky)=0;
public:
    renderer();
    void setFlush(flushf flush_callback);
    void init(videoData vd);
    virtual void specificInit() {
        
    };
    
    
    
    
    virtual ~renderer();
public:
    virtual void render()=0;
};


#endif	/* RENDERERABSTRACT_HPP */

