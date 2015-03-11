#ifndef LIBLOAD_HPP
#define	LIBLOAD_HPP

#include <string>
#include <vector>
#include <iostream>
#include <dlfcn.h>

using namespace std;

#include "misc/singleton.hpp"
#include "renderer/rendererAbstract.hpp"

/*
 To możnaby potraktować jako fabrykę, przywoływaną zawsze do pobrania danego podsystemu
 */

typedef void * lib_handle;
typedef vector<lib_handle> lib_vector;

class LibLoad : public Singleton<LibLoad> {
protected:
    lib_vector libs;
    lib_handle load(string fn);
public: 
    
    RendererAbstract * getRenderer(string name);
    ~LibLoad();
    
};

#endif	/* LIBLOAD_HPP */

