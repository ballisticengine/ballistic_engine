#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include "singleton.hpp"
#include "types.hpp"
#include "texture.hpp"
#include "skybox.hpp"

struct videoData {
    int width,height,bpp;
    
};

typedef  void (*flushf)();

class renderer : public singleton {
protected:
    videoData vd;
    flushf flush_callback;
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

