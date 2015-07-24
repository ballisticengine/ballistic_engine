#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "misc/singleton.hpp"

typedef void (*flush_function)();

class RenderingManager : public Singleton<RenderingManager> {
public:
    void init();
    void render();
    virtual void setFlush(flush_function flush_callback);
};

#endif

