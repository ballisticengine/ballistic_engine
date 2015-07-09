#ifndef LIBLOAD_HPP
#define	LIBLOAD_HPP

#include <string>
#include <vector>
#include <iostream>
#include <dlfcn.h>

using namespace std;

#include "misc/singleton.hpp"
#include "renderer/rendererAbstract.hpp"
#include "io/sdlio.hpp"

/*
 To możnaby potraktować jako fabrykę, przywoływaną zawsze do pobrania danego podsystemu
 */

typedef void * lib_handle;
typedef vector<lib_handle> lib_vector;

class LibLoad : public Singleton<LibLoad> {
protected:
    lib_vector libs;
    void error(string name);
    lib_handle load(string fn);
public: 
    
    RendererAbstract * getRenderer(string name);
//    SdlIO * getIO();
    ~LibLoad();
    
};

#endif	/* LIBLOAD_HPP */

