#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "misc/singleton.hpp"
#include "config/path.hpp"
#include "types/Resource.hpp"
#include "libload/LibLoad.hpp"
#include "misc/utils.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/
class LoadedResource {

public:
    LoadedResource(void *object, Resource *resource);
    void *object;
    Resource *resource;
};

class Factory   {
protected:
	string wd,lvl;
	map <string,LoadedResource *> items;
	vector <LoadedResource *> item_ptr;
	bool force_common,uses_common;
        virtual LoadedResource * actualLoad(string fn, string orig_fn)=0;
        virtual string getSubDir()=0;
        static void abort(string reason="");
        
public:
	 Factory();
	 virtual ~Factory();
	 virtual void * get(string fn,bool force_common=false,bool clone=false);
	 virtual vector <LoadedResource *> getAll();
	 virtual void setWD(string wd);
         virtual void setLevel(string lvl);
	
};

#endif