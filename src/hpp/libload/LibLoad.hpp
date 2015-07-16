#ifndef LIBLOAD_HPP
#define	LIBLOAD_HPP

#include <string>
#include <map>
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

class Module {
public:
    lib_handle handle;
    string entry_point_name, file_name;
    void *module_class;
};


typedef vector<lib_handle> lib_vector;
typedef map<string, Module> lib_map;

class LibLoad : public Singleton<LibLoad> {
protected:
    lib_map libs;
    void error(string name);
    Module loadLib(string file_name, string entry_point_name);
public: 
    void loadLoader(string file_name);
    void discoverLoaders();
    void registerModule(string name, string file_name, string entry_point_name);
    void * getModuleClass(string name);
//    SdlIO * getIO();
    ~LibLoad();
    
};

#endif	/* LIBLOAD_HPP */

