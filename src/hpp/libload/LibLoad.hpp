#ifndef LIBLOAD_HPP
#define	LIBLOAD_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <dlfcn.h>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs=boost::filesystem;

#include "misc/singleton.hpp"
#include "resources/Loader.hpp"
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


typedef vector<Module> lib_vector;
typedef map<string, Module> lib_map;

class LibLoad : public Singleton<LibLoad> {
protected:
    lib_map libs;
    lib_vector loads;
    void error(string name);
    Module loadLib(string file_name, string entry_point_name);
public: 
    void registerLoader(string file_name);
    void discoverLoaders();
    Loader * getLoaderByExtension(string ext, ResourceType type=NONE);
    void registerModule(string name, string file_name, string entry_point_name);
    void * getModuleClass(string name);
    lib_vector &  getAllLoaders();
//    SdlIO * getIO();
    ~LibLoad();
    
};

#endif	/* LIBLOAD_HPP */

